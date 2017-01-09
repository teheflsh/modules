<?php

/**
 * @file
 * Build page for token_api.
 */

/**
 * Token API page content.
 */
function successful_content() {
  global $user;
  $message = '';
  if ($user->uid != 0) {
    $message = variable_get('token_api_message', 'Hello!');
    $message = token_replace($message);
  }
  return $message;
}
