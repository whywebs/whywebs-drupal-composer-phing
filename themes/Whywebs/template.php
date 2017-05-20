<?php
/**
 * @file
 * Template file for the nuovo template.
 */


/**
 * Variables preprocess function for the "page" theming hook.
 */
function whywebs_preprocess_page(&$vars, $hook) {
  if (isset($vars['node'])) {
  // If the node type is "blog" the template suggestion will be "page--blog.tpl.php".
   $vars['theme_hook_suggestions'][] = 'page__'. str_replace('_', '--', $vars['node']->type);
  }
  if (isset($vars['main_menu'])) {
    $vars['main_menu'] = theme('links__system_main_menu', array(
      'links' => $vars['main_menu'],
      'attributes' => array(
        'class' => array('links', 'main-menu', 'clearfix'),
      ),
      'heading' => array(
        'text' => t('Main menu'),
        'level' => 'h2',
        'class' => array('element-invisible'),
      )
    ));
  }
  else {
    $vars['main_menu'] = FALSE;
  }
  if (isset($vars['secondary_menu'])) {
    $vars['secondary_menu'] = theme('links__system_secondary_menu', array(
      'links' => $vars['secondary_menu'],
      'attributes' => array(
        'class' => array('links', 'secondary-menu', 'clearfix'),
      ),
      'heading' => array(
        'text' => t('Secondary menu'),
        'level' => 'h2',
        'class' => array('element-invisible'),
      )
    ));
  }
  else {
    $vars['secondary_menu'] = FALSE;
  }
}

function whywebs_form_alter(&$form, &$form_state, $form_id) {

  if ($form_id == "user_login_block") {
    //$form['links'] = Null; // Remove Request New Password and other links from Block form
    //$form['links']['#markup'] = t('Forgotten Password?') . ' ' . t('Forgotten Password?') . ''; // Remove Request New Password from Block form
    $form['links']['#markup'] = ' ' . t('Register') . '' . ' ' . t('Forgotten Password?') . ''; // Remove Request New Password from Block form
    $form['name']['#title'] = Null; // Change text on form
    $form['name']['#attributes'] = array('placeholder' => t('username'));
    $form['pass']['#title'] = Null;
    $form['pass']['#attributes'] = array('placeholder' => t('password'));
  }
}

function whywebs_theme($existing, $type, $theme, $path){
  $hooks['user_register_form']=array(
    'render element'=>'form',
    'template' =>'tpl/system/user-register',
  );
return $hooks;
}

function whywebs_preprocess_user_register(&$variables) {
  $variables['form'] = drupal_build_form('user_register_form', user_register_form(array()));
}
