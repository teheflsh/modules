<?php

/**
 * @file
 * Create custom function for token_api.
 */

 /**
  * Custom function for add new record fo token_api table.
  */
function token_api_record() {
  global $user;

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'token_api');
  $result = $query->execute();

  foreach ($result['token_api'] as $record) {
    $records[] = $record->tid;
  }

  $tids = entity_load('token_api', $records);

  foreach ($tids as $tid) {
    $uids[] = $tid->uid;
  }

  /* Check user existence in token_api */
  $token = '';
  if (in_array($user->uid, $uids) == FALSE) {
    /* Record discount_codes in token_api */
    foreach ($tids as $tid) {
      $discount_codes[] = $tid->discount_code;
    }

    $temp = token_api_generate_token();

    if (in_array($temp, $discount_codes) == FALSE) {
      $token = $temp;
    }

    $table_name = 'token_api';
    $row = new stdClass();
    $row->uid = $user->uid;
    $row->discount_code = $token;
    drupal_write_record($table_name, $row);
  }
}

/**
 * Custom function for generate token.
 */
function token_api_generate_token() {
  $characters = '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ';
  $charactersLength = strlen($characters);
  $token = '';

  for ($i = 0; $i < 10; $i++) {
    $token .= $characters[rand(0, $charactersLength - 1)];
  }

  return $token;
}
