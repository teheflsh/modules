<?php

/**
 * @file
 * Build page for token_api.
 */

/**
 * Token API page content.
 */
function token_api_page_content() {
  $message = variable_get('token_api_message', 'Hello!');
  $message = token_replace($message);
  return $message;
}
