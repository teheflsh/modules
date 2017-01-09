<?php

/**
 * @file
 * Build form for token_api.
 */

/**
 * Build token_api form for redirect after user register.
 */
function token_api_form_alter(&$form, &$form_state, $form_id) {
  if ($form_id == 'user_register_form') {
    $form['#submit'][] = 'token_api_user_register_submit';
  }
}

/**
 * Custom function Register Submit for token_api.
 */
function token_api_user_register_submit($form, &$form_state) {
  $form_state['redirect'] = 'successful';
}

/**
 * Build node_views_entity form.
 */
function token_api_form($form, &$form_state, $token_api, $op = 'edit') {
  $form['uid'] = array(
    '#title' => 'UID',
    '#type' => 'textfield',
    '#required' => TRUE,
  );
  $form['discount_code'] = array(
    '#title' => 'Discount Code',
    '#type' => 'textfield',
    '#required' => TRUE,
  );

  $form['actions'] = array(
    '#type' => 'actions',
  );

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Сохранить',
  );

  return $form;
}

/**
 * Submit button for node_views_entity.
 */
function token_api_form_submit(&$form, &$form_state) {
  $token_api = entity_ui_form_submit_build_entity($form, $form_state);
  $token_api->save();
  $form_state['redirect'] = 'admin/config/custom/token_api';
}
