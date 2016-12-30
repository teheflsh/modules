<?php

/**
 * @file
 * Build admin form for token_api.
 */

 /**
  * Token API config form.
  */
function token_api_config_form($form, &$form_state) {
  $form = array();

  $form['token_api_message'] = array(
    '#type' => 'textarea',
    '#title' => t('Token API Message'),
    '#default_value' => variable_get('token_api_message', 'Hello!'),
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
