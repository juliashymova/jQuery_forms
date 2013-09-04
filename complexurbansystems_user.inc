<?php
module_load_include('inc', 'user', 'user.pages');


/** * Define a collaboration request form. */

function complexurbansystems_contact_form($form, &$form_state) {
  $form['user_name'] = array(
      '#title' => t('Your name'),
      '#type' => 'textfield',
      '#description' => t('Please enter your name.'),
      '#required' => TRUE,
  );
  $form['mail'] = array(
      '#title' => t('Your e-mail address'),
      '#type' => 'textfield',
      '#description' => t('Please enter your e-mail address.'),
      '#required' => TRUE,
  );
  $form['request'] = array(
      '#title' => t('Your request'),
      '#type' => 'textarea',
      '#description' => t('Please enter your request.'),
      '#required' => TRUE,
  );
  $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Submit')
  );
  //asaf_prepare_form($form, $form_state, array('submit'));
  return $form;
}

function complexurbansystems_contact_form_validate($form, &$form_state) {
  if (!valid_email_address($form_state['values']['mail'])) {
    $mail = $form_state['values']['mail'];
    form_set_error('mail', t('The e-mail address @mail is not valid.', array('@mail' => $mail)));
  }
}

function complexurbansystems_contact_form_submit($form, &$form_state) {
  $module = 'complexurbansystems';
  $key = 'collaboration_request';
  $to = variable_get("site_mail");
  $body = array("Name: ".$form_state['values']['user_name'],
      "E-mail: ".$form_state['values']['mail'],
      "Request: ".$form_state['values']['request']
  );

  drupal_mail($module, $key, $to, NULL, array('body' => $body));
  drupal_set_message(t("Your request has been sent! We will contact you soon."));
}


function complexurbansystems_form_user_pass_alter(&$form, &$form_state, $form_id) {
  $form['#submit'][] = 'complexurbansystems_user_pass_submit';
}

function complexurbansystems_user_pass_submit($form, &$form_state) {
  unset($form_state['redirect']);
}


function complexurbansystems_form_user_register_form_alter(&$form, &$form_state, $form_id) {
  $form['#submit'][] = 'complexurbansystems_user_register_submit';
}

function complexurbansystems_user_register_submit($form, &$form_state) {
  unset($form_state['redirect']);
}
