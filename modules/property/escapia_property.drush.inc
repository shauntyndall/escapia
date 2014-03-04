<?php


function escapia_property_drush_command() {
  $items = array();

  $items['ep-full-import'] = array(
    'callback' => 'escapia_property_drush_full_import',
    'description' => dt('Process all customers in the queue.'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    'aliases' => array('ep-fi'),
  );

  $items['ep-process-queues'] = array(
    'description' => 'A command to process items on the Queue.',
    'options' => array(
      'threads' => 'The number of threads to use.',
      'limit' => 'The total number of jobs to put on the Queue.',
      'batch_size' => 'How many items from the Queue to process in each thread. Default is 10.',
      'queue' => 'Which queue to process.',
    ),
    'aliases' => array('ep-pq'),
  );

  $items['ep-process-property-queue'] = array(
    'description' => 'A command to process items on the Queue.',
    'options' => array(
      'threads' => 'The number of threads to use.',
      'limit' => 'The total number of jobs to put on the Queue.',
      'batch_size' => 'How many items from the Queue to process in each thread. Default is 10.',
      'queue' => 'Which queue to process.',
    ),
    'aliases' => array('ep-ppq'),
  );

  $items['ep-consumer'] = array(
    'description' => 'A single consumer process.',
    'arguments' => array(
      'limit' => 'The number of jobs to process on the Queue',
    ),
  );

  $items['ep-property-consumer'] = array(
    'description' => 'A single consumer process.',
    'arguments' => array(
      'limit' => 'The number of jobs to process on the Queue',
    ),
  );

  return $items;
}

/**
 * Trigger a full property import.
 */
function escapia_property_drush_full_import() {
  // set the time out to infinite
  set_time_limit(0);
  $api = new EscapiaPropertyImportAPI();
  $api->fullDataImport();
}

/**
 *
 */
function drush_escapia_property_ep_process_queues() {
  $time = time();
  $threads = drush_get_option('threads', 1);
  $batch_size = drush_get_option('batch_size', 10);
  $queue = DrupalQueue::get('EscapiaPropertyData', TRUE);
  $queue_size = $queue->numberOfItems();

  try {
    drush_print("Going to work on {$queue_size} items from the Queue with {$threads} threads...");
    drush_thread_manager($queue_size, $batch_size, $threads, '_ep_setup');
  }
  catch (Exception $e) {
    drush_set_error($e->getMessage());
  }

  $time = time() - $time;
  drush_print("Time taken with {$threads} threads: {$time} seconds");
}

function drush_escapia_property_ep_process_property_queue() {
  $time = time();
  $threads = drush_get_option('threads', 1);
  $batch_size = drush_get_option('batch_size', 10);
  $queue = DrupalQueue::get('EscapiaPropertyData', TRUE);
  $queue_size = $queue->numberOfItems();

  try {
    drush_print("Going to work on {$queue_size} items from the property queue with {$threads} threads...");
    drush_thread_manager($queue_size, $batch_size, $threads, '_ep_property_setup');
  }
  catch (Exception $e) {
    drush_set_error($e->getMessage());
  }

  $time = time() - $time;
  drush_print("Time taken with {$threads} threads: {$time} seconds");
}

/**
 * A multi threaded setup function.
 *
 * @param int $thread_id
 *  An identifier for the thread which will execute this command.
 * @param int $batch_size
 *  How many tasks this command should work on.
 * @param int $offset
 *  The position in a Queue of jobs for the first job this command
 *  should work on.
 *
 * @return string
 *  A command which can be executed on the command line.
 */
function _ep_setup($thread_id, $batch_size, $offset) {
  return "drush ep-consumer $batch_size";
}

/**
 * A multi threaded property import setup function.
 *
 * @param int $thread_id
 *  An identifier for the thread which will execute this command.
 * @param int $batch_size
 *  How many tasks this command should work on.
 * @param int $offset
 *  The position in a Queue of jobs for the first job this command
 *  should work on.
 *
 * @return string
 *  A command which can be executed on the command line.
 */
function _ep_property_setup($thread_id, $batch_size, $offset) {
  return "drush ep-property-consumer $batch_size";
}

function drush_escapia_property_ep_property_consumer($limit = 10) {
  $queue = DrupalQueue::get('EscapiaPropertyData', TRUE);

  for ($count = 0; $count < $limit; $count++) {

    if ($item = $queue->claimItem()) {
      $transaction = db_transaction(__FUNCTION__);

      try {
        _ep_process_property_item($item->data);
      }
      catch (Exception $e) {
        $transaction->rollback();
        drush_set_error($e->getMessage());
        $queue->releaseItem($item);
        return;
      }

      // Unset the transaction to force a commit.
      unset($transaction);
      $queue->deleteItem($item);
    }

  }
}

/**
 * Process a property from the queue.
 * @param $data
 */
function _ep_process_property_item($data) {
  $api = new EscapiaPropertyImportAPI();
  $api->processProperty($data);
  usleep(rand(100000, 1000000));
}