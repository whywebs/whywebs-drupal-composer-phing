<?php
/**
 * @file
 * Admin page callback file for the simplified_social_share module.
 */
// Define LoginRadius domain
define('LR_DOMAIN', 'api.loginradius.com');
/**
 * Show admin form of simplified social share.
 *
 * @param $form : form element at admin page
 * @param $form_state
 * @return mixed
 */
function simplified_social_share_admin_settings($form, &$form_state) {
  global $base_url, $user;
  $my_path = drupal_get_path('module', 'simplified_social_share');
  drupal_add_library('system', 'ui.sortable');
  // Add js file to show Login/register js interface at admin page.
  drupal_add_js($my_path . '/simplified_social_share.js');
  drupal_add_css($my_path . '/simplified_social_share.admin.css');
  // Add js options that require to show login/register js interface.
  $api_key = trim(variable_get('socialsharing_api_key'));
  if (!isset($api_key) || empty($api_key)) {
    drupal_add_js('//hub.loginradius.com/cdn/Include/js/LoginRadius.1.0.js');
    drupal_add_js($my_path . '/simplified_social_share.loginradius-aia.js');
    drupal_add_js('LoginRadiusAIA.$hooks.setProcessHook(function () {
                       jQuery("#processing_img_div").html("<img width=20 height=20 src=' . $base_url . '/' . $my_path . '/images/loading.gif style=float:left;margin-right:5px; /><span style=color:blue;width:auto>Please wait. This may take a few minutes ...</span>");
                 }, function () {
            });
            $SL.util.ready(function () {
            var aiaOptions = {};
            var regorlogin;
            aiaOptions.inFormvalidationMessage = true;
            aiaOptions.website = "www.loginradius.com";
            aiaOptions.WebTechnology = "Drupal";
			aiaOptions.Emailid = "' . $user->mail . '";
			var login_error_message = jQuery("#login_error_message");
            var register_form_link = jQuery("#register_form_link");
            var processing_img_div= jQuery("#processing_img_div");
            LoginRadiusAIA.init(aiaOptions, "registration", function (response) {
            login_error_message.removeClass("messages error");
            register_form_link.css("display", "none");
            var html = "<div id=loginRadiusFormDiv><select id=lrSites class=form-hiddenselect style = display:none >";
            for (var i = 0; i < response.length; i++) {
                html += "<option value= " + response[i].apikey + " selected >" + response[i].appName + "</option>";
            }
            html += "</select><br/>";
            html += "<div id=login_radius_message style=margin-top:18px;></div></div>";
            jQuery("#edit-login-register").after(html);
            processing_img_div.html("");
            // Save LR site name after registration.
            loginRadiusSaveLRSite("registration");

        }, function (errors) {
            if (errors[0].description) {
                processing_img_div.html("");
                login_error_message.html(errors[0].description).css("color", "red");
                login_error_message.addClass("messages error");
            }

        }, "registeration-container");
        LoginRadiusAIA.init(aiaOptions, "login", function (response) {
        login_error_message.removeClass("messages error");
        login_error_message.html("");
        processing_img_div.html("");
        register_form_link.css("display", "none");
        jQuery("#dynamic_form_heading").html("Site Selection");
        var html = "<div id=loginRadiusFormDiv><label for=lrSites>Select a LoginRadius site</label><select id=lrSites class=form-select><option value=>--Select a Site--</option>";
        for (var i = 0; i < response.length; i++) {
            html += "<option value= " + response[i].apikey + " >" + response[i].appName + "</option>";
        }
        html += "</select><br/>";
        html += "<input type=button id=loginRadiusLRSiteSave class=form-submit value=Save style=margin-top:15px;float:left;  /><div id=login_radius_message style=margin-top:18px;></div></div>";
        jQuery("#edit-socialsharing-form-login").html(html);
        document.getElementById("loginRadiusLRSiteSave").onclick = function () {
            loginRadiusSaveLRSite("login");
        };
        }, function (errors) {
        if (errors[0].description) {
            processing_img_div.html("");
            jQuery("#loadingimage").css("display", "none");
            login_error_message.html(errors[0].description).css("color", "red");
            login_error_message.addClass("messages error");
        }

        }, "login-container");
        });
', array('type' => 'inline'));
  }
  // End js options.
  // Add Js code to show horizontal and vertical sharing tab at admin page.
  drupal_add_js('jQuery(document).ready(function () {
    var horizontal_image = "' . variable_get("socialsharing_horizontal_images") . '";
    var vertical_image = "' . variable_get("socialsharing_vertical_images") . '";
    if (horizontal_image == 8 || horizontal_image == 9) {
        counter_horizontal_show();
    } else {
        sharing_horizontal_show();
        if (horizontal_image == 2 || horizontal_image == 3) {
            sharing_simple_horizontal_show();
        }
    }
    if (vertical_image == 6 || vertical_image == 7) {
        counter_vertical_show();
    } else {
        sharing_vertical_show();
    }
    var selected_theme = "' . variable_get("socialsharing_selected_share_interface") . '";
    if (selected_theme == "vertical") {
        hidden_horizontal_widget();
    } else {
        display_horizontal_widget();
    }
});
// Save LR site when user register to loginradius.
function loginRadiusSaveLRSite() {
        var login_radius_message = jQuery("#login_radius_message");
        var processing_img_div = jQuery("#processing_img_div");
        if (jQuery("#lrSites").val().trim() == "") {
            jQuery("#login_radius_message").html("Please select a site").css("color", "red");
            return;
        }
        login_radius_message.html("<img width=20 height=20 src=' . $base_url . '/' . $my_path . '/images/loading.gif style=float:left;margin-right:5px; /><span style=color:blue;width:auto>Please wait. This may take a few minutes ...</span>");
        jQuery.ajax({
             type: "POST",
             url: "' . url("simplified_social_share/login_submit") . '",
             data: {
                 apikey: jQuery("#lrSites").val().trim(),
             },
        success: function (data, textStatus, XMLHttpRequest) {
               if (data.message == "success") {
                   location.href = location.href;
               } else {
                   // unexpected error
                   login_radius_message.html("Unexpected error occurred,").css("color", "red");
                   processing_img_div.html("");
               }
           },
           error: function (a, b, c) {
               processing_img_div.html("");
               login_radius_message.html("Unexpected error occurred, message not returned").css("color", "red");
           }
       });
       }', array('type' => 'inline', 'scope' => 'header', 'weight' => 5));
  // Add thanks text to show at admin page.
  $thanks_text = t('<a href="@loginradius" target="_blank">LoginRadius</a> provides <a href="@social-login" target="_blank">Social Login</a>,
  <a href="@social-share" target="_blank">Social Share</a>,
  <a href="@social-invite" target="_blank">Social Invite</a>,
  <a href="@user-profile" target="_blank">User Social Profile Data</a>,
  <a href="@user-profile-access" target="_blank">User Profile Access</a>,
  <a href="@sso" target="_blank">Single Sign-On</a>,
  <a href="@social-analytics" target="_blank">Social Engagement  Analytics</a> as single Unified API.<br/><br/> We also have ready to use plugins for
  <a href="@wordpress" target="_blank">Wordpress</a>,
  <a href="@joomla" target="_blank">Joomla</a>,
  <a href="@magento" target="_blank">Magento</a>,
  <a href="@oscommerce" target="_blank">osCommerce</a>,
  <a href="@zencart" target="_blank">Zen-Cart</a>,
  <a href="@xcart" target="_blank">X-Cart</a>,
  <a href="@prestashop" target="_blank">Prestashop</a>,
  <a href="@vanillaforum" target="_blank">VanillaForum</a>,
  <a href="@vbulletin" target="_blank">vBulletin</a>,
  <a href="@phpbb" target="_blank">phpBB</a>,
  <a href="@smf" target="_blank">SMF</a> and
  <a href="@dotnetnuke" target="_blank">DotNetNuke</a>',
    array(
      '@loginradius' => 'http://www.loginradius.com',
      '@social-share' => 'http://ish.re/9RZO',
      '@sso' => 'http://ish.re/9RZS',
      '@social-invite' => 'http://ish.re/9RZQ',
      '@user-profile' => 'http://ish.re/83Y8',
      '@user-profile-access' => 'http://ish.re/83Y8',
      '@social-analytics' => 'http://ish.re/AQ5L',
      '@joomla' => 'http://ish.re/8PE6',
      '@wordpress' => 'http://ish.re/96IF',
      '@vbulletin' => 'http://ish.re/8PED',
      '@vanillaforum' => 'http://ish.re/8PEE',
      '@magento' => 'http://ish.re/8PEC',
      '@oscommerce' => 'http://ish.re/8PEG',
      '@prestashop' => 'http://ish.re/8PEH',
      '@xcart' => 'http://ish.re/8PFQ',
      '@zencart' => 'http://ish.re/96IC',
      '@dotnetnuke' => 'http://ish.re/96IA',
      '@phpbb' => 'http://ish.re/96I8',
      '@smf' => 'http://ish.re/96I9',
      '@get_sociallogin' => 'http://ish.re/1MP',
      '@social-login' => 'http://ish.re/9RZM'
    ));
  // show module details.
  $update_text = t('Module Version: 2.1 <br/> Author : LoginRadius <br/> Website: <a href="@loginradius" target="_blank">https://www.loginradius.com</a> <br/> Community : <a href="@community" target="_blank">http://community.loginradius.com</a> <br/>To receive updates on new features, future releases and other updates, please connect with us on<br/>
  <a  href="https://www.facebook.com/loginradius" target="_blank"><img src="' . $base_url . '/' . $my_path . '/images/footer-media-links/facebook.png" /></a>
  <a href="https://twitter.com/LoginRadius" target="_blank"><img src="' . $base_url . '/' . $my_path . '/images/footer-media-links/twitter.png" /></a>
  <a href="https://plus.google.com/+Loginradius" target="_blank"> <img src="' . $base_url . '/' . $my_path . '/images/footer-media-links/google.png" /></a>
  <a href="http://www.linkedin.com/company/loginradius" target="_blank"> <img src="' . $base_url . '/' . $my_path . '/images/footer-media-links/linkedin.png" /></a>
  <a href="https://www.youtube.com/user/LoginRadius" target="_blank"> <img src="' . $base_url . '/' . $my_path . '/images/footer-media-links/youtube.png" /></a>
', array(
      '@loginradius' => 'https://www.Loginradius.com/',
      '@community' => 'http://community.loginradius.com',
      '@facebook' => 'https://www.facebook.com/loginradius',
      '@twitter' => 'https://twitter.com/LoginRadius',
      '@linkedin' => 'http://www.linkedin.com/company/2748191?trk=tyah'
    ));
  $form['thanks_block'] = array(
    '#type' => 'fieldset',
    '#title' => t('Thank you for installing the LoginRadius Simplified Social Share module!'),
    '#description' => $thanks_text,
    '#attributes' => array('style' => 'float:left'),
  );
  $form['update_block'] = array(
    '#type' => 'fieldset',
    '#title' => t('Get Updates'),
    '#description' => $update_text,
  );
  //show login/register interface.
  $api_key = trim(variable_get('socialsharing_api_key'));
  if (!isset($api_key) || empty($api_key)) {
    $group = 'login_register';
    $form[$group] = array(
      '#title' => '<h3 id = "dynamic_form_heading" style ="margin: 0px !important;text-transform: none;">Create a LoginRadius Account</h3>',
      '#type' => 'fieldset',
      '#attributes' => array('style' => 'clear:both'),
    );
    $form[$group]['socialsharing_form_login'] = array(
      '#prefix' => '<div id="login_error_message"></div>',
      '#type' => 'item',
      '#markup' => '<div id = "registeration-container" style="margin-top: 20px;"></div><div id = "login-container"  style = "display:none;margin-top: 20px;"></div>',

    );
    $form[$group]['lr_linktextregister'] = array(
      '#type' => 'item',
      '#prefix' => '<div id = processing_img_div></div>',
      '#id' => 'register_form_link',
      '#markup' => '<a href="javascript:void(0)"  id="lr_toggle_form_link" style="text-decoration:none" onclick=lr_toggle_form("login")>New to LoginRadius, Register Now! </a><br/><a href="https://secure.loginradius.com/login/forgotten" style="text-decoration:none" target="_blank">Forgot your password?</a>',
    );
    $form[$group]['lr_linktextlogin'] = array(
      '#type' => 'item',
      '#id' => 'login_form_link',
      '#markup' => '<a  href="javascript:void(0)" style="text-decoration:none" id="lr_toggle_form_link1" onclick=lr_toggle_form("register")>Already have an account?</a><br/><a href="https://secure.loginradius.com/login/forgotten" style="text-decoration:none" target="_blank">Forgot your password?</a>',

    );
  }
  //Show all settings when user is sucessfully registered/logged in to loginradius.
  else {
    $group = 'share';
    $form[$group] = array(
      '#type' => 'fieldset',
      '#title' => t('Social Sharing Settings'),
      '#attributes' => array('style' => 'clear:both'),
    );
    $form[$group]['socialsharing_api_key'] = array(
      '#type' => 'textfield',
      '#title' => t('API Key'),
      '#default_value' => variable_get('socialsharing_api_key', ''),
    );
    $form[$group]['socialsharing_horizontal'] = array(
      '#type' => 'item',
      '#prefix' => '<div><b>' . t('<div class="description">Please select the social sharing widget, horizontal and vertical widgets can be enabled simultaneously.</div>') . '</b></div>',
      '#markup' => ' <div id="lr_tabs"><ul><li><a id="socialsharing_horizontal" onclick="display_horizontal_widget();">Horizontal widget</a></li><li><a id="socialsharing_veritical" onclick="hidden_horizontal_widget();">Vertical widget</a></li></ul>'
      //'#markup' => l(t('Horizontal'), "javascript:void(0)", array('fragment' => '', 'external' => TRUE, 'attributes' => array('id' => 'socialsharing_horizontal', 'onclick' => 'display_horizontal_widget();'))) . "<b>|</b>" . l(t('Vertical'), "javascript:void(0)", array('fragment' => '', 'external' => TRUE, 'attributes' => array('id' => 'socialsharing_veritical', 'onclick' => 'hidden_horizontal_widget();' )))
    );
    $form[$group]['socialsharing_selected_share_interface'] = array(
      '#type' => 'hidden',
      '#title' => t('selected share interface'),
      '#default_value' => variable_get('socialsharing_selected_share_interface'),
      '#suffix' => '<div id="show_horizontal_block">',
    );
    $form[$group]['socialsharing_enable_horizontal_share'] = array(
      '#type' => 'radios',
      '#title' => t('Do you want to enable horizontal social sharing for your website?'),
      '#default_value' => variable_get('socialsharing_enable_horizontal_share', 1),
      '#options' => array(
        1 => t('Yes'),
        0 => t('No'),
      )
    );
    $form[$group]['socialsharing_enable_vertical_share'] = array(
      '#type' => 'radios',
      '#title' => t('Do you want to enable vertical  social sharing for your website?'),
      '#default_value' => variable_get('socialsharing_enable_vertical_share', 0),
      '#options' => array(
        1 => t('Yes'),
        0 => t('No'),
      )
    );
    $form[$group]['socialsharing_horizontal_images'] = array(
      '#type' => 'radios',
      '#id' => 'socialsharing_horizontal_images',
      '#title' => t('Select your social sharing widget:'),
      '#default_value' => variable_get('socialsharing_horizontal_images', 0),
      '#options' => array(
        0 => '<img src="' . $base_url . '/' . $my_path . '/images/horizonSharing32.png" id="horizon_sharing32"></img>',
        1 => '<img src="' . $base_url . '/' . $my_path . '/images/horizonSharing16.png" id="horizon_sharing16"></img>',
        2 => '<img src="' . $base_url . '/' . $my_path . '/images/single-image-theme-large.png" id="single-image-theme-large"></img>',
        3 => '<img src="' . $base_url . '/' . $my_path . '/images/single-image-theme-small.png" id="single-image-theme-small"></img>',
        8 => '<img src="' . $base_url . '/' . $my_path . '/images/horizontalvertical.png" id="horizontalvertical"></img>',
        9 => '<img src="' . $base_url . '/' . $my_path . '/images/horizontal.png" id="horizontal"></img>',
      ),
    );
    $form[$group]['socialsharing_vertical_images'] = array(
      '#type' => 'radios',
      '#id' => 'socialsharing_vertical_images',
      '#default_value' => variable_get('socialsharing_vertical_images', 4),
      '#options' => array(
        4 => '<img src="' . $base_url . '/' . $my_path . '/images/32VerticlewithBox.png"></img>',
        5 => '<img id="VerticlewithBox" src="' . $base_url . '/' . $my_path . '/images/16VerticlewithBox.png"></img>',
        6 => '<img id="hybrid-verticle-vertical" src="' . $base_url . '/' . $my_path . '/images/hybrid-verticle-vertical.png"></img>',
        7 => '<img id="hybrid-verticle-horizontal"  src="' . $base_url . '/' . $my_path . '/images/hybrid-verticle-horizontal.png"></img>',
      ),
      '#attributes' => array('style' => 'display:block'),
    );
    $form[$group]['socialsharing_show_horizotal'] = array(
      '#type' => 'hidden',
      '#suffix' => '<div id="socialsharing_show_horizotal_widget">',
    );
    $counter_providers = variable_get('socialsharingcounter_rearrange_providers_list');
    if (empty($counter_providers)) {
      variable_set('socialsharingcounter_rearrange_providers_list', simplified_social_share_get_default_sharing_networks('socialsharingcounter_rearrange_providers_list'));
    }
    $form[$group]['socialsharing_counter_show_providers_list'] = array(
      '#type' => 'item',
      '#id' => 'socialcounter_show_providers_list',
      '#class' => 'form-item form-type-checkboxes form-item-socialshare-counter-show-providers-list',
      '#title' => t('What sharing networks do you want to show in the sharing widget? (All other sharing networks will be shown as part of LoginRadius sharing icon)'),
      '#default_value' => variable_get('socialsharingcounter_rearrange_providers_list'),
      '#suffix' => '<div id="socialcounter_hidden_field" style="display:none;">',
    );
    foreach (variable_get("socialsharingcounter_rearrange_providers_list") as $provider) {
      if (!empty($provider)) {
        $raw = $provider;
        $provider = str_replace(' ', '', $provider);
        $provider = str_replace("++", "plusplus", $provider);
        $provider = str_replace("+", "plus", $provider);
        $form[$group][$provider] = array(
          '#type' => 'item',
          '#attributes' => array('class' => array('lrshare_' . $provider)),
          '#markup' => '<input type = "hidden" id = "input-lrcounter-' . $provider . '" name = "socialsharingcounter_rearrange_providers_list[]" value = "' . $raw . '" />',
        );
      }
    }
    $share_providers = variable_get("socialsharing_rearrange_providers_list");
    if (empty($share_providers)) {
      variable_set('socialsharing_rearrange_providers_list', simplified_social_share_get_default_sharing_networks('socialsharing_rearrange_providers_list'));
    }
    $form[$group]['socialsharing_show_providers_list'] = array(
      '#type' => 'item',
      '#id' => 'socialsharing_providers_list',
      '#title' => t('What sharing networks do you want to show in the sharing widget? (All other sharing networks will be shown as part of LoginRadius sharing icon)'),
      '#default_value' => variable_get('socialsharing_rearrange_providers_list'),
      '#prefix' => '</div><div id="loginRadiusSharingLimit" style="color:red; display:none; margin-bottom: 5px;">' . t('You can select only 9 providers.') . '</div>',
      '#suffix' => '<div id="rearrange_sharing_text"><b>' . t('What sharing network order do you prefer for your sharing widget? Drag the icons around to set the order') . '</b></div><ul id="socialsharing_rearrange_providers" class="socialsharing_rearrange_providers">',
    );
    foreach (variable_get("socialsharing_rearrange_providers_list") as $provider) {
      if (!empty($provider)) {
        $form[$group]['lrshare_iconsprite32' . $provider] = array(
          '#type' => 'item',
          '#attributes' => array('class' => array('lrshare_' . $provider)),
          '#markup' => '<li id = "edit-lrshare-iconsprite32' . $provider . '" class = "lrshare_iconsprite32 lrshare_' . $provider . '" title = "' . $provider . '" >
          <input type = "hidden" id = "input-lrshare-' . $provider . '" name = "socialsharing_rearrange_providers_list[]" value = "' . $provider . '" /></li>',
        );
      }
    }
    $form[$group]['socialsharing_rearran_providers_list'] = array(
      '#type' => 'hidden',
      '#prefix' => '</ul><div id="socialsharing_question"></div>',
      '#suffix' => '</div>',
    );
    $form[$group]['socialsharing_show_veritical'] = array(
      '#type' => 'hidden',
      '#suffix' => '<div id="socialsharing_show_veritcal_widget">',
    );
    $counter_providers = variable_get('socialsharingcounter_vertical_rearrange_providers_list');
    if (empty($counter_providers)) {
      variable_set('socialsharingcounter_vertical_rearrange_providers_list', simplified_social_share_get_default_sharing_networks('socialsharingcounter_vertical_rearrange_providers_list'));
    }
    $form[$group]['socialsharing_counter_vertical_show_providers_list'] = array(
      '#type' => 'item',
      '#id' => 'socialcounter_vertical_show_providers_list',
      '#title' => t('What sharing networks do you want to show in the sharing widget? (All other sharing networks will be shown as part of LoginRadius sharing icon)'),
      '#default_value' => variable_get('socialsharingcounter_vertical_rearrange_providers_list'),
      '#suffix' => '<div id="socialcounter_vertical_hidden_field" style="display:none;">',
    );
    foreach (variable_get("socialsharingcounter_vertical_rearrange_providers_list") as $provider) {
      if (!empty($provider)) {
        $raw = $provider;
        $provider = str_replace(' ', '', $provider);
        $provider = str_replace("++", "plusplus", $provider);
        $provider = str_replace("+", "plus", $provider);
        $form[$group]['lrshare_vertical_' . $provider] = array(
          '#type' => 'item',
          '#attributes' => array('class' => array('lrshare_vertical_' . $provider)),
          '#markup' => '<input type = "hidden" id = "input-lrcounter-vertical-' . $provider . '" name = "socialsharingcounter_vertical_rearrange_providers_list[]" value = "' . $raw . '" />',
        );
      }
    }
    $share_providers = variable_get("socialsharing_vertical_rearrange_providers_list");
    if (empty($share_providers)) {
      variable_set('socialsharing_vertical_rearrange_providers_list', simplified_social_share_get_default_sharing_networks('socialsharing_vertical_rearrange_providers_list'));
    }
    $form[$group]['socialsharing_vetical_show_providers_list'] = array(
      '#type' => 'item',
      '#id' => 'socialsharing_vetical_show_providers_list',
      '#title' => t('What sharing networks do you want to show in the sharing widget? (All other sharing networks will be shown as part of LoginRadius sharing icon)'),
      '#default_value' => variable_get('socialsharing_vertical_rearrange_providers_list'),
      '#prefix' => '</div><div id="loginRadiusSharingLimit_vertical" style="color:red; display:none; margin-bottom: 5px;">' . t('You can select only 9 providers.') . '</div>',
      '#suffix' => '<div id="rearrange_sharing_text_vertical"><b>' . t('What sharing network order do you prefer for your sharing widget?(Drag around to set the order)') . '</b></div><ul id="socialsharing_vertical_rearrange_providers" class="socialsharing_vertical_rearrange_providers">',
    );
    foreach (variable_get("socialsharing_vertical_rearrange_providers_list") as $provider) {
      if (!empty($provider)) {
        $form[$group]['lrshare_iconsprite32_vertical' . $provider] = array(
          '#type' => 'item',
          '#attributes' => array('class' => array('lrshare_' . $provider)),
          '#markup' => '<li id = "edit-lrshare-iconsprite32_vertical' . $provider . '" class = "lrshare_iconsprite32 lrshare_' . $provider . '" title = "' . $provider . '" >
          <input type = "hidden" id = "input-lrshare-vertical-' . $provider . '" name = "socialsharing_vertical_rearrange_providers_list[]" value = "' . $provider . '" /></li>',
        );
      }
    }
    $form[$group]['socialsharing_vertical_rearra_providers_list'] = array(
      '#type' => 'hidden',
      '#prefix' => '</ul><div id="socialsharing_question"></div>',
      '#suffix' => '</div>',
    );
    $form[$group]['socialsharing_vertical_images']['socialsharing_vertical_position'] = array(
      '#type' => 'radios',
      '#title' => t('Select the position of social sharing widget'),
      '#weight' => 50,
      '#default_value' => variable_get('socialsharing_vertical_position', 0),
      '#options' => array(
        0 => t('Top Left'),
        1 => t('Top Right'),
        2 => t('Bottom Left'),
        3 => t('Bottom Right'),
      ),
    );
    $form[$group]['socialsharing_horizontal_location'] = array(
      '#title' => t('What location do you want to show the social sharing widget?'),
      '#type' => 'radios',
      '#options' => array(
        '0' => t('Node content'),
        '1' => t('Links area'),
      ),
      '#default_value' => variable_get('socialsharing_horizontal_location', '0'),
      '#attributes' => array('onclick' => 'display_block_horizontal(this.value);'),
    );
    $form[$group]['socialsharing_position_top'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show at the top of content.'),
      '#default_value' => variable_get('socialsharing_position_top', 1) ? 1 : 0,
      '#prefix' => '<div id="horizontal_sharing_show"> <b>Select the position of social sharing interface</b>',
    );
    $form[$group]['socialsharing_position_bottom'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show at the bottom of content.'),
      '#default_value' => variable_get('socialsharing_position_bottom', 1) ? 1 : 0,
      '#suffix' => '</div>',
    );
    $form[$group]['socialsharing_show_pages'] = array(
      '#type' => 'radios',
      '#title' => t('Show social share on specific pages'),
      '#default_value' => variable_get('socialsharing_show_pages', 0),
      '#options' => array(
        0 => t('All pages except those listed'),
        1 => t('Only the listed pages'),
      ),
    );
    $form[$group]['socialsharing_show_exceptpages'] = array(
      '#type' => 'textarea',
      '#default_value' => variable_get('socialsharing_show_exceptpages', ''),
      '#description' => t('Enter the page title(s) (in the same format provided during page creation) or node ID (if url is http://example.com/node/1 then enter 1) separated by commas'),
      '#rows' => 5,
    );
    $form[$group]['socialsharing_vertical_show_pages'] = array(
      '#type' => 'radios',
      '#title' => t('Show social sharing only on specific pages'),
      '#default_value' => variable_get('socialsharing_vertical_show_pages', 0),
      '#options' => array(
        0 => t('All pages except those listed'),
        1 => t('Only the listed pages'),
      ),
    );
    $form[$group]['socialsharing_vertical_show_exceptpages'] = array(
      '#type' => 'textarea',
      '#default_value' => variable_get('socialsharing_vertical_show_exceptpages', ''),
      '#description' => t('Enter the page title(s) (in the same format provided during page creation) or node ID (if url is http://example.com/node/1 then enter 1) separated by commas'),
      '#rows' => 5,
      '#suffix' => '</div>',
    );
    $form['#submit'][] = 'simplified_social_share_admin_settings_submit';
    $form['actions'] = array('#type' => 'actions');
    $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save configuration'),
    );
  }
  return $form;
}

/**
 * Validate the Simplified Social share settings.
 */
function simplified_social_share_admin_settings_validate($form, &$form_state) {
  simplified_social_share_save_network_providers($form_state);
  $string = '~1#' . $form_state['values']['socialsharing_enable_horizontal_share'] . '|' . $form_state['values']['socialsharing_horizontal_images'] . '|["' . implode('","', variable_get('socialsharing_rearrange_providers_list')) . '"]';
  $string .= '|["' . implode('","', variable_get('socialsharingcounter_rearrange_providers_list')) . '"]' . '|' . $form_state['values']['socialsharing_horizontal_location'] . '|' . $form_state['values']['socialsharing_position_top'] . '|' . $form_state['values']['socialsharing_position_bottom'] .
    '|' . $form_state['values']['socialsharing_show_pages'] . '|"' . $form_state['values']['socialsharing_show_exceptpages'] . '"';
  $string .= '|' . $form_state['values']['socialsharing_enable_vertical_share'] . '|' . $form_state['values']['socialsharing_vertical_images'] . '|' . $form_state['values']['socialsharing_vertical_position'] . '|["' . implode('","', variable_get('socialsharing_vertical_rearrange_providers_list')) . '"]';
  $string .= '|["' . implode('","', variable_get('socialsharingcounter_vertical_rearrange_providers_list')) . '"]' . '|' . $form_state['values']['socialsharing_vertical_show_pages'] . '|"' . $form_state['values']['socialsharing_vertical_show_exceptpages'] . '"';
  $api_key = trim($form_state['values']['socialsharing_api_key']);
  $validateurl = 'https://' . LR_DOMAIN . '/api/v2/app/validatekey?apikey=' . rawurlencode($api_key);
  $data = array(
    'addon' => 'Drupal',
    'version' => '2.1',
    'agentstring' => $_SERVER["HTTP_USER_AGENT"],
    'clientip' => $_SERVER["REMOTE_ADDR"],
    'configuration' => $string,
  );
  try {
    $result = simplified_social_share_api_client($validateurl, $data);
    $result = json_decode($result);
    if (isset($result->Status) && !$result->Status) {
      $error = array();
      $error['API_KEY_NOT_FORMATED'] = "LoginRadius API Key is not formatted correctly";
      $error['API_KEY_NOT_VALID'] = "LoginRadius API key is invalid. Get your LoginRadius API key from <a href='http://www.loginradius.com' target='_blank'>LoginRadius</a>";
      foreach ($result->Messages as $value) {
        form_set_error('', check_plain($error["$value"]));
        return;
      }
    }
  } catch (Exception $e) {
    watchdog_exception('type', $e);
  }
}

/**
 * Submit the Simplified Social share settings.
 */
function simplified_social_share_admin_settings_submit($form, &$form_state) {
  simplified_social_share_save_network_providers($form_state);
  // Clean all values and save into database.
  foreach ($form_state['input'] as $key => $value) {
    if (is_array($value)) {
      variable_set($key, array_filter($value));
    }
  }
  form_state_values_clean($form_state);
  foreach ($form_state['values'] as $key => $value) {
    if (isset($form_state['values']['array_filter']) && is_array($value)) {
      $value = array_keys(array_filter($value));
    }
    variable_set($key, $value);
  }
  drupal_set_message(t('The configuration options have been saved.'));
  cache_clear_all();
  menu_rebuild();
}

/*
 * Save sharing networks.
 */
function simplified_social_share_save_network_providers(&$form_state) {
  // Set default value of sharing networks.
  $settings = array(
    'socialsharing_rearrange_providers_list',
    'socialsharingcounter_rearrange_providers_list',
    'socialsharing_vertical_rearrange_providers_list',
    'socialsharingcounter_vertical_rearrange_providers_list'
  );
  foreach ($settings as $value) {
    simplified_social_share_save_network_providers_submit($form_state, $value);
  }
}

/*
 * @param $key: check sharing or counter admin variables.
 *
 * Set defalt values into database.
 */
function simplified_social_share_save_network_providers_submit(&$form_state, $network) {
  if (isset($form_state['input'][$network])) {
    $form_state['input'][$network] = array_filter($form_state['input'][$network]);
  }
  else {
    $form_state['input'][$network] = simplified_social_share_get_default_sharing_networks($network);
  }
}

/*
 * @param $key: check sharing or counter.
 * @return mixed|string
 *
 * Get default values of sharing/counter.
 */
function simplified_social_share_get_default_sharing_networks($key) {
  $data = array();
  if ($key == 'socialsharing_rearrange_providers_list' || $key == 'socialsharing_vertical_rearrange_providers_list') {
    $data = array(
      "0" => "facebook",
      "1" => "googleplus",
      "2" => "google",
      "3" => "pinterest",
      "4" => "twitter",
    );
  }
  else {
    $data = array(
      "0" => "Facebook Like",
      "1" => "Google+ +1",
      "2" => "Pinterest Pin it",
      "3" => "LinkedIn Share",
    );
  }
  return $data;
}