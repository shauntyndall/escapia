<?php

/**
 * A multithreading manager for drush.
 *
 * @param int $job_count
 *   The total number of jobs to process
 * @param int $job_batch_size
 *   The number of jobs handed to each thread
 * @param int $thread_count
 *   The maximum number of active threads
 * @param string $setup_function
 *   The function to generate the thread command. This is written for your
 *   application its signature is:
 *   my_setup_function($thread_id, $limit, $offset) : string;
 *   Where $thread_id is the unique thread identifier, $limit is the total
 *   number of records to process and offset is the starting point. The
 *   function should return a string which is a shell command that the thread
 *   will execute in a separate process.
 * @param string $teardown_function
 *   A function which runs when a thread completes. It's signature is:
 *   my_teardown_function($thread_id);
 *   Your business logic can then run any cleanup which occurs when the
 *   thread completes.
 * @param int $starting_offset
 *   (optional) Start x records into the process.
 */
function drush_thread_manager($job_count, $job_batch_size, $thread_count, $setup_function, $teardown_function = '', $starting_offset = 0) {

  if (!function_exists('proc_open')) {
    throw new Exception('proc_open command is needed to use multi threading.');
  }

  $jobs_remaining = $job_count;
  $processes = array();
  $running = TRUE;
  $offset = $starting_offset;
  $start = time();

  $descriptor_spec = array(
    0 => array("pipe", "r"),
    1 => array("pipe", "w"),
    2 => array("pipe", "w"),
  );

  while ($running) {

    // Fill all empty threads.
    for ($thread_id = 0; $thread_id < $thread_count; $thread_id++) {
      if ($jobs_remaining > 0 && !isset($processes[$thread_id])) {
        $pipes = array();
        $cmd = $setup_function($thread_id, $job_batch_size, $offset);
        $process = proc_open($cmd, $descriptor_spec, $pipes);

        drush_print("Thread {$thread_id} starts at offset $offset. Jobs remaining: $jobs_remaining");

        foreach ($pipes as $pipe) {
          stream_set_blocking($pipe, FALSE);
        }

        $offset += $job_batch_size;
        $jobs_remaining -= $job_batch_size;

        $processes[$thread_id] = array(
          'process' => $process,
          'pipes' => $pipes,
        );

        //sleep(1);
      }
    }

    // Monitor running threads.
    for ($thread_id = 0; $thread_id < $thread_count; $thread_id++) {
      if (!isset($processes[$thread_id])) {
        continue;
      }

      $process_running = _mt_monitor_process($thread_id, $processes[$thread_id]['process'], $processes[$thread_id]['pipes']);

      if (!$process_running) {
        unset($processes[$thread_id]);

        if (!empty($teardown_function)) {
          $teardown_function($thread_id);
        }

        $speed = ($job_count - $jobs_remaining) / (time() - $start);
        $end_date = date('G:i:s d/m/y', ($job_count / $speed) + $start);
        $speed = floor($speed * 60);

        drush_print("Thread {$thread_id} finished. Average speed is {$speed} jobs/minute. Estimated completion at {$end_date}");
      }
    }

    // Check for endgame.
    if ($jobs_remaining < 1 && empty($processes)) {
      $running = FALSE;
    }
    else {
      // Pause the master process.
      sleep(1);
    }
  }
}

/**
 * Monitor a process.
 *
 * This function checks a running process.
 * If it has finished it is closed down safely.
 *
 * @return bool
 *   TRUE if the process is still running
 *   FALSE if it is not running.
 */
function _mt_monitor_process($thread_id, $process, $pipes) {
  $status = proc_get_status($process);

  foreach ($pipes as $id => $pipe) {
    if ($id == 0) {
      // Don't read from stdin!
      continue;
    }

    $messages = stream_get_contents($pipe);

    if (!empty($messages)) {
      foreach (explode("\n", $messages) as $message) {
        $message = str_replace('[error]', '', $message);
        $message = str_replace('[completed]', '', $message);
        $message = trim($message);
        if (!empty($message)) {
          if ($id == 1) {
            // Message from stdout.
            drush_print(" -> T$thread_id: $message");
          }
          else {
            // Message from stderr.
            drush_set_error(" -> T$thread_id: $message");
          }
        }
      }
    }
  }

  if (!$status['running']) {
    foreach ($pipes as $pipe) {
      fclose($pipe);
    }

    proc_close($process);
  }

  return $status['running'];
}