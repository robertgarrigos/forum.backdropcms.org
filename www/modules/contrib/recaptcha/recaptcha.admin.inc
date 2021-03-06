<?php

/**
 * @file
 * Provides the Google No CAPTCHA administration settings.
 */

/**
 * Form callback; administrative settings for Google No CAPTCHA.
 */
function recaptcha_admin_settings() {
  $config = config('recaptcha.settings');

  $form = array();
  $form['recaptcha_general_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('General settings'),
  );
  $form['recaptcha_general_settings']['recaptcha_site_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Site key'),
    '#default_value' => $config->get('site_key'),
    '#maxlength' => 40,
    '#description' => t('The site key given to you when you <a href="@url">register for reCAPTCHA</a>.', array('@url' => 'http://www.google.com/recaptcha/admin')),
    '#required' => TRUE,
  );
  $form['recaptcha_general_settings']['recaptcha_secret_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Secret key'),
    '#default_value' => $config->get('secret_key'),
    '#maxlength' => 40,
    '#description' => t('The secret key given to you when you <a href="@url">register for reCAPTCHA</a>.', array('@url' => 'http://www.google.com/recaptcha/admin')),
    '#required' => TRUE,
  );
  $form['recaptcha_widget_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Widget settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['recaptcha_widget_settings']['recaptcha_theme'] = array(
    '#type' => 'select',
    '#title' => t('Theme'),
    '#description' => t('Defines which theme to use for reCAPTCHA.'),
    '#options' => array(
      'light' => t('Light (default)'),
      'dark' => t('Dark'),
    ),
    '#default_value' => $config->get('theme'),
  );
  $form['recaptcha_widget_settings']['recaptcha_type'] = array(
    '#type' => 'select',
    '#title' => t('Type'),
    '#description' => t('The type of CAPTCHA to serve.'),
    '#options' => array(
      'image' => t('Image (default)'),
      'audio' => t('Audio'),
    ),
    '#default_value' => $config->get('type'),
  );
  $form['recaptcha_widget_settings']['recaptcha_size'] = array(
    '#default_value' => $config->get('size'),
    '#description' => t('The size of CAPTCHA to serve.'),
    '#options' => array(
      '' => t('Normal (default)'),
      'compact' => t('Compact'),
    ),
    '#title' => t('Size'),
    '#type' => 'select',
  );
  $form['recaptcha_widget_settings']['recaptcha_tabindex'] = array(
    '#type' => 'textfield',
    '#title' => t('Tabindex'),
    '#description' => t('Set the <a href="@tabindex">tabindex</a> of the widget and challenge (Default = 0). If other elements in your page use tabindex, it should be set to make user navigation easier.', array('@tabindex' => 'http://www.w3.org/TR/html4/interact/forms.html#adef-tabindex')),
    '#default_value' => $config->get('tabindex'),
    '#size' => 4,
  );
  $form['recaptcha_widget_settings']['recaptcha_noscript'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable fallback for browsers with JavaScript disabled'),
    '#default_value' => $config->get('noscript'),
    '#description' => t('If JavaScript is a requirement for your site, you should <strong>not</strong> enable this feature. With this enabled, a compatibility layer will be added to the captcha to support non-js users.'),
  );
  // Add a submit button
  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );
  return $form;
}

/**
 * Validation function for recaptcha_admin_settings().
 *
 * @see recaptcha_admin_settings()
 */
function recaptcha_admin_settings_validate($form, &$form_state) {
  $tabindex = $form_state['values']['recaptcha_tabindex'];
  if (!is_numeric($tabindex)) {
    form_set_error('recaptcha_tabindex', t('The tabindex must be an integer.'));
  }
}

/*
 * Add a submit function to process config
 *
 * @see recaptcha_admin_settings()
 */
function recaptcha_admin_settings_submit($form, &$form_state) {
  $config = config('recaptcha.settings');
  $config->set('site_key', $form_state['values']['recaptcha_site_key']);
  $config->set('secret_key', $form_state['values']['recaptcha_secret_key']);
  $config->set('theme', $form_state['values']['recaptcha_theme']);
  $config->set('type', $form_state['values']['recaptcha_type']);
  $config->set('size', $form_state['values']['recaptcha_size']);
  $config->set('tabindex', $form_state['values']['recaptcha_tabindex']);
  $config->set('noscript', $form_state['values']['recaptcha_noscript']);
  $config->save();
  backdrop_set_message(t('The configuration options have been saved.'));
}
