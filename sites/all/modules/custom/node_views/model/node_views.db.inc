<?php

/**
 * @file
 * Functions for working with the database in a module node_views.
 */

/**
 * Function for selection views on all nodes in a node_views_config_page_view().
 */
function node_views_page_view() {
  $nodes = db_select('node_views', 'n');
  $nodes->fields('n', array('title', 'nodeid'));
  $nodes->orderBy('n.title');
  $count = $nodes->addExpression('count(title)', 'count');
  $nodes->groupBy('n.title');
  return $result = $nodes->execute();
}

/**
 * Function for selection views on all nodes in a node_views_config_page_view().
 */
function node_views_page_node_view($nodeid) {
  $nodes = db_select('node_views', 'n');
  $nodes->fields('n', array('nodeid', 'title', 'username', 'created'));
  $nodes->condition('nodeid', $nodeid, '=');
  $nodes->orderBy('n.title');
  $result = $nodes->execute();
  return $result = $nodes->execute();
}
