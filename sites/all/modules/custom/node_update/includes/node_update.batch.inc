<?php

/**
 * @file
 * Run batch for node_update.
 */

/**
 * Update the fields in the nodes.
 */
function node_update_update($nodes, &$context) {
  if (empty($context['sandbox'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['prev_nid'] = 0;
    $context['sandbox']['max'] = db_select('node')->countQuery()->execute()->fetchField();
  }

  $nid = db_select('node', 'n')
    ->fields('n', array('nid'))
    ->condition('nid', $context['sandbox']['prev_nid'], '>')
    ->execute()
    ->fetchField();
  $node = node_load($nid);
  $wrapper = entity_metadata_wrapper('node', $node);
  $wrapper->field_latest_updates = time();
  $wrapper->save();

  $node_wrapper = entity_metadata_wrapper('node', $node);
  $raw_collection = $node_wrapper->field_rate_date[0]->value();
  $collection = entity_metadata_wrapper('field_collection_item', $raw_collection);
  $collection->field_rate = rand(0, 100);
  $collection->field_date = time();
  $collection->save();

  $context['sandbox']['progress']++;
  $context['sandbox']['prev_nid'] = $nid;
  $context['results']['titles'][] = $node->title;
  $context['message'] = 'Update <em>' . check_plain($node->title) . '</em>';

  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}

/**
 * Finish callback for Batch.
 */
function node_update_batch_finished($success, $results, $operations) {
  if ($success) {
    drupal_set_message(t('Update finished'));
  }
  else {
    drupal_set_message(t('Finished with an error.'));
  }
}
