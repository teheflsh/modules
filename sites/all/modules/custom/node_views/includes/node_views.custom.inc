<?php

/**
 * @file
 * Build custom form for node_views.
 */

/**
 * Function for show views on all nodes.
 */
function node_views_config_page_view() {
  $result = node_views_page_view();
  $header = array('title', 'count');
  $rows = array();

  foreach ($result as $node) {
    $rows[] = array(
      '<a href="/node/' . $node->nodeid . '">' . $node->title . '</a>',
      '<a href="/admin/config/custom/node_views/' . $node->nodeid . '">' . $node->count . '</a>',
    );
  }

  return theme('table', array('header' => $header, 'rows' => $rows));
}

/**
 * Function for show views on current nodes.
 */
function node_views_config_page_node_view($nodeid) {
  $result = node_views_page_node_view($nodeid);
  $header = array('username', 'created');
  $rows = array();

  foreach ($result as $node) {
    $rows[] = array($node->username, $node->created);
  }

  return theme('table', array('header' => $header, 'rows' => $rows));
}
