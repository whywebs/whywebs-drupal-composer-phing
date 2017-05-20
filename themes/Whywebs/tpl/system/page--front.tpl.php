<?php

/**
 * @file
 * Default theme implementation to display a single Drupal page.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/bartik.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['highlighted']: Items for the highlighted content region.
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['sidebar_second']: Items for the second sidebar.
 * - $page['header']: Items for the header region.
 * - $page['footer']: Items for the footer region.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see template_process()
 */
?>
<div id="sticky-wrapper">
<?php if ($page['top_menu']): ?>
  <header id="header" role="banner">
    <div class="wrapper">
      <?php print render($page['top_menu']); ?>
    </div>
  </header>
<?php endif; ?>


  <div id="header-image" role="banner">
    
      <video loop muted autoplay class="video">
          <source src="../sites/all/themes/whywebs/Whywebs/mp4/homepage1.mp4" type="video/mp4">   
      </video> 
      <!-- <img src="../sites/all/themes/whywebs/Whywebs/img/bigwig_login.jpg"> -->
      <div class="grey"> 
     <?php if ($page['header']): ?>

      <?php print render($page['header']); ?>

      <?php endif; ?>
      </div>
  </div>


<?php if ($page['banner']): ?>
  <div id="header-banner" role="banner">
      <?php print render($page['banner']); ?>
  </div>
<?php endif; ?>

<?php if ($page['highlight']): ?>
  <div id="highlight">
  	<div class="wrapper">

  	  <?php print render($page['highlight']); ?>
  	</div>
  </div>
<?php endif; ?>

<?php if ($page['homepage_intro']): ?>
  <div id="top_main_intro">
        <?php print render($page['homepage_intro']); ?>
  </div>
<?php endif; ?>
<?php if ($page['homepage_1']): ?>
  <div id="homepage-secret-weapon">


        <?php print render($page['homepage_1']); ?>
  </div>
<?php endif; ?>

<?php if ($page['homepage_2']): ?>
  <div id="homepage-we-serve">
        <?php print render($page['homepage_2']); ?>
  </div>
<?php endif; ?>

<?php if ($page['main_prefix']): ?>
	<div id="main-prefix">
  	<div class="wrapper">
  	  <?php print render($page['main_prefix']); ?>
  	</div>
	</div>
<?php endif; ?>

<?php if ($page['intro']): ?>
	<div id="main_intro">
  	<div class="wrapper">
  	  <?php print render($page['intro']); ?>
  	</div>
	</div>
<?php endif; ?>

<?php if ($page['cta']): ?>
	<div id="cta">
  	<div class="wrapper">
  	  <?php print render($page['cta']); ?>
  	</div>
	</div>
<?php endif; ?>

<?php if ($page['main_suffix_menu_1'] || $page['main_suffix_menu_2'] || $page['main_suffix_menu_3'] || $page['main_suffix_menu_4'] || $page['main_suffix_menu_5']): ?>
   <div id="homepage-suffix-menu">
    <?php print render($page['main_suffix_menu_1']); ?>
    <?php print render($page['main_suffix_menu_2']); ?>
    <?php print render($page['main_suffix_menu_3']); ?>
    <?php print render($page['main_suffix_menu_4']); ?>
    <?php print render($page['main_suffix_menu_5']); ?>
  <div>
<?php endif; ?>

<?php if ($page['main_suffix']): ?>
	<div class="wrapper">
	  <?php print render($page['main_suffix']); ?>
	</div>
<?php endif; ?>



<?php if ($page['footer']): ?>
  <footer id="footer" role="contentinfo">
	  <div class="wrapper">
	    <?php print render($page['footer']); ?>

	  </div>
  </footer>
<?php endif; ?>
</div>