<?php

/**
 * @file
 * Create new rules for keywords.
 */

/**
 * Implements hook_rules_event_info().
 */
function keywords_rules_event_info() {
  return array(
    'keywords_node_update' => array(
      'label' => t('Node update'),
      'module' => 'keywords',
      'group' => t('Custom'),
    ),
  );
}

/**
 * Implements hook_default_rules_configuration().
 */
function keywords_default_rules_configuration() {
  $rule = rules_reaction_rule();
  $rule->label = 'Node Update';
  $rule->active = TRUE;
  $rule->event('keywords_node_update');

  $configs['keywords_default'] = $rule;
  return $configs;
}

/**
 * Implements hook_node_update().
 */
function keywords_node_update($node) {
  $message = 'Keywords: ';
  $node_keyword = array();
  $keyword = array();
  $nid = db_select('node', 'n')
    ->fields('n', array('nid', 'type'))
    ->condition('n.type', 'keywords_test')
    ->execute()
    ->fetchField();
  $kids = db_select('keywords', 'n')
    ->fields('n', array('keyword'))
    ->execute();
  $node = node_load($nid);
  $node_wrapper = entity_metadata_wrapper('node', $node);

  foreach ($node_wrapper->field_keywords as $field_collection_wrapper) {
    $raw_collection = $field_collection_wrapper->value();
    $raw_collection = entity_metadata_wrapper('field_collection_item', $raw_collection);
    $node_keyword[] = $raw_collection->field_keyword->value();
  }

  foreach ($kids as $kid) {
    $keyword[] = $kid->keyword;
  }

  $compare_keywords = array_intersect($keyword, $node_keyword);

  foreach ($compare_keywords as $compare_keyword) {
    $message .= $compare_keyword . '/';
  }

  watchdog('keywords', $message);
}
