<?php

/**
 * @file
 * Create custom function for user_discount.
 */

 /**
  * Custom function for add new record fo user_discount table.
  */
function user_discount_record() {
  global $user;

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'user_discount');
  $result = $query->execute();

  foreach ($result['user_discount'] as $record) {
    $records[] = $record->tid;
  }

  $tids = entity_load('user_discount', $records);

  foreach ($tids as $tid) {
    $uids[] = $tid->uid;
  }

  /* Check user existence in user_discount */
  $token = '';
  if (in_array($user->uid, $uids) == FALSE) {
    /* Record discount_codes in user_discount */
    foreach ($tids as $tid) {
      $discount_codes[] = $tid->discount_code;
    }

    $temp = user_discount_generate_token();

    if (in_array($temp, $discount_codes) == FALSE) {
      $token = $temp;
    }

    $table_name = 'user_discount';
    $row = new stdClass();
    $row->uid = $user->uid;
    $row->discount_code = $token;
    drupal_write_record($table_name, $row);
  }
}

/**
 * Custom function for generate token.
 */
function user_discount_generate_token() {
  $characters = '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ';
  $charactersLength = strlen($characters);
  $token = '';

  for ($i = 0; $i < 10; $i++) {
    $token .= $characters[rand(0, $charactersLength - 1)];
  }

  return $token;
}
