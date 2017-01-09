<?php

/**
 * @file
 * Build admin form for user_discount.
 */

 /**
  * User Discount config form.
  */
function user_discount_config_form($form, &$form_state) {
  $form = array();

  $form['user_discount_message'] = array(
    '#type' => 'textarea',
    '#title' => t('User Discount Message'),
    '#default_value' => variable_get('user_discount_message', 'Hello!'),
    '#required' => TRUE,
  );
  $form['token_tree'] = array(
    '#type' => 'fieldset',
    '#title' => t('Replacement patterns'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => theme('token_tree', array('token_types' => array('user'))),
    '#weight' => 10,
  );

  return system_settings_form($form);
}
