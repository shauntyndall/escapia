<?php

/**
 * Implements hook_drush_command().
 * @return array
 */
function escapia_import_drush_command() {
  $items = array();

  $items['ei-full-import'] = array(
    'callback' => 'escapia_import_drush_full_import',
    'description' => dt('Retrieve all properties and put them into queue.'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    'aliases' => array('ei-fi'),
  );

  $items['ei-flush'] = array(
    'callback' => 'escapia_import_drush_property_flush',
    'description' => dt('Flush all escapia property entity data.'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    'aliases' => array('ei-f'),
  );

  $items['ei-process-queues'] = array(
    'description' => 'A command to process items on the Queue.',
    'options' => array(
      'threads' => 'The number of threads to use.',
      'limit' => 'The total number of jobs to put on the Queue.',
      'batch_size' => 'How many items from the Queue to process in each thread. Default is 10.',
      'queue' => 'Which queue to process.',
    ),
    'aliases' => array('ei-pq'),
  );

  $items['ei-process-property-queue'] = array(
    'description' => 'A command to process items on the Queue.',
    'options' => array(
      'threads' => 'The number of threads to use.',
      'limit' => 'The total number of jobs to put on the Queue.',
      'batch_size' => 'How many items from the Queue to process in each thread. Default is 10.',
      'queue' => 'Which queue to process.',
    ),
    'aliases' => array('ei-ppq'),
  );

  $items['ei-process-photo-queue'] = array(
    'description' => 'A command to process items on the Queue.',
    'options' => array(
      'threads' => 'The number of threads to use.',
      'limit' => 'The total number of jobs to put on the Queue.',
      'batch_size' => 'How many items from the Queue to process in each thread. Default is 10.',
      'queue' => 'Which queue to process.',
    ),
    'aliases' => array('ei-phq'),
  );

  $items['ei-process-rate-queue'] = array(
    'description' => 'A command to process items on the Queue.',
    'options' => array(
      'threads' => 'The number of threads to use.',
      'limit' => 'The total number of jobs to put on the Queue.',
      'batch_size' => 'How many items from the Queue to process in each thread. Default is 10.',
      'queue' => 'Which queue to process.',
    ),
    'aliases' => array('ei-prq'),
  );

  $items['ei-consumer'] = array(
    'description' => 'A single consumer process.',
    'arguments' => array(
      'limit' => 'The number of jobs to process on the Queue',
    ),
  );

  $items['ei-property-consumer'] = array(
    'description' => 'A single consumer process for properties.',
    'arguments' => array(
      'limit' => 'The number of jobs to process on the Queue',
    ),
  );

  $items['ei-property-photo-consumer'] = array(
    'description' => 'A single consumer process for property photo queues.',
    'arguments' => array(
      'limit' => 'The number of jobs to process on the Queue',
    ),
  );

  $items['ei-property-rate-consumer'] = array(
    'description' => 'A single consumer process for property rate queues.',
    'arguments' => array(
      'limit' => 'The number of jobs to process on the Queue',
    ),
  );

  return $items;
}

/**
 * Trigger a full property import.
 */
function escapia_import_drush_full_import() {
  // set the time out to infinite
  set_time_limit(0);
  $api = new EscapiaImport();
  $api->importAll();
}

/**
 * Drush wrapper to flush all Escapia properties from the system.
 */
function escapia_import_drush_property_flush() {
  set_time_limit(0);
  $task = new EscapiaImport();
  $task->propertyFlush();
}

/**
 * Process all queue items related to Escapia.
 */
function drush_escapia_import_ep_process_queues() {
  $time = time();
  $threads = drush_get_option('threads', 1);
  $batch_size = drush_get_option('batch_size', 10);
  $queue = DrupalQueue::get('EscapiaProperty', TRUE);
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

/**
 * Process EscapiaProperty queue items.
 */
function drush_escapia_import_ep_process_property_queue() {
  $time = time();
  $threads = drush_get_option('threads', 1);
  $batch_size = drush_get_option('batch_size', 10);
  $queue = DrupalQueue::get('EscapiaProperty', TRUE);
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
 * Process EscapiaPropertyRate queue items.
 */
function drush_escapia_import_ep_process_rate_queue() {
  $time = time();
  $threads = drush_get_option('threads', 1);
  $batch_size = drush_get_option('batch_size', 10);
  $queue = DrupalQueue::get('EscapiaPropertyRate', TRUE);
  $queue_size = $queue->numberOfItems();

  try {
    drush_print("Going to work on {$queue_size} items from the property queue with {$threads} threads...");
    drush_thread_manager($queue_size, $batch_size, $threads, '_ep_property_rate_setup');
  }
  catch (Exception $e) {
    drush_set_error($e->getMessage());
  }

  $time = time() - $time;
  drush_print("Time taken with {$threads} threads: {$time} seconds");
}

/**
 * Process EscapiaPropertyPhoto queue items.
 */
function drush_escapia_import_ep_process_photo_queue() {
  $time = time();
  $threads = drush_get_option('threads', 1);
  $batch_size = drush_get_option('batch_size', 10);
  $queue = DrupalQueue::get('EscapiaPropertyPhoto', TRUE);
  $queue_size = $queue->numberOfItems();

  try {
    drush_print("Going to work on {$queue_size} items from the property queue with {$threads} threads...");
    drush_thread_manager($queue_size, $batch_size, $threads, '_ep_property_photo_setup');
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
  return "drush ei-consumer $batch_size";
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
  return "drush ei-property-consumer $batch_size";
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
function _ep_property_photo_setup($thread_id, $batch_size, $offset) {
  return "drush ei-property-photo-consumer $batch_size";
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
function _ep_property_rate_setup($thread_id, $batch_size, $offset) {
  return "drush ei-property-rate-consumer $batch_size";
}

/**
 * Consumer to process threads from the DrupalQueue.
 * @param int $limit
 */
function drush_escapia_import_ep_property_consumer($limit = 10) {
  $queue = DrupalQueue::get('EscapiaProperty', TRUE);

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
 * Consumer to process threads from the DrupalQueue.
 * @param int $limit
 */
function drush_escapia_import_ep_property_photo_consumer($limit = 10) {
  $queue = DrupalQueue::get('EscapiaPropertyPhoto', TRUE);

  for ($count = 0; $count < $limit; $count++) {

    if ($item = $queue->claimItem()) {
      $transaction = db_transaction(__FUNCTION__);

      try {
        _ep_process_property_photo_item($item->data);
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
 * Consumer to process threads from the DrupalQueue.
 * @param int $limit
 */
function drush_escapia_import_ep_property_rate_consumer($limit = 10) {
  $queue = DrupalQueue::get('EscapiaPropertyRate', TRUE);

  for ($count = 0; $count < $limit; $count++) {

    if ($item = $queue->claimItem()) {
      $transaction = db_transaction(__FUNCTION__);

      try {
        _ep_process_property_rate_item($item->data);
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
  $connection = escapia_connection_load($data['connection_id']);
  $api = new EscapiaAPI($connection);

  if ($property = $api->getUnitInfo($data['UnitCode'])) {
    $import_api = new EscapiaImport();
    $import_api->processProperty($property);
  }

  usleep(rand(100000, 1000000));
}

/**
 * Process a property photo from the queue.
 * @param $data
 */
function _ep_process_property_photo_item($data) {
  $connection = escapia_connection_load($data['connection_id']);
  $api = new EscapiaAPI($connection);

  if ($property = $api->getUnitInfo($data['UnitCode'])) {
    $import_api = new EscapiaImport();
    $import_api->processPhotos($property);
  }

  usleep(rand(100000, 1000000));
}

/**
 * Process a property photo from the queue.
 * @param $data
 */
function _ep_process_property_rate_item($data) {
  $connection = escapia_connection_load($data['connection_id']);
  $api = new EscapiaAPI($connection);

  if ($property = $api->getUnitInfo($data['UnitCode'])) {
    // @todo replace with variables for dates
    if ($rates = $api->getUnitRateRange($data['UnitCode'], strtotime('01/1/2014'), strtotime('12/31/2014'))) {
      $xml = simplexml_load_string($rates->xmlResponse);
      $xml->registerXPathNamespace("ns", EscapiaAPI::SOAP_NAMESPACE);
      $property->availability = (string) @end($xml->xpath('//ns:DailyAvailability'));
    }

    $import_api = new EscapiaImport();
    $import_api->processRates($property);
  }

  usleep(rand(100000, 1000000));
}