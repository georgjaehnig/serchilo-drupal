<?php
/**
 * @file
 * serchilo.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function serchilo_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'shortcuts';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Shortcuts';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Shortcuts';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Field: Content: Keyword */
  $handler->display->display_options['fields']['field_keyword']['id'] = 'field_keyword';
  $handler->display->display_options['fields']['field_keyword']['table'] = 'field_data_field_keyword';
  $handler->display->display_options['fields']['field_keyword']['field'] = 'field_keyword';
  $handler->display->display_options['fields']['field_keyword']['element_label_colon'] = FALSE;
  /* Field: Content: argument_names */
  $handler->display->display_options['fields']['field_argument_names']['id'] = 'field_argument_names';
  $handler->display->display_options['fields']['field_argument_names']['table'] = 'field_data_field_argument_names';
  $handler->display->display_options['fields']['field_argument_names']['field'] = 'field_argument_names';
  $handler->display->display_options['fields']['field_argument_names']['label'] = 'Arguments';
  $handler->display->display_options['fields']['field_argument_names']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Namespace */
  $handler->display->display_options['fields']['field_namespace']['id'] = 'field_namespace';
  $handler->display->display_options['fields']['field_namespace']['table'] = 'field_data_field_namespace';
  $handler->display->display_options['fields']['field_namespace']['field'] = 'field_namespace';
  $handler->display->display_options['fields']['field_namespace']['element_label_colon'] = FALSE;
  /* Field: Content: Tags */
  $handler->display->display_options['fields']['field_tags']['id'] = 'field_tags';
  $handler->display->display_options['fields']['field_tags']['table'] = 'field_data_field_tags';
  $handler->display->display_options['fields']['field_tags']['field'] = 'field_tags';
  $handler->display->display_options['fields']['field_tags']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_tags']['delta_offset'] = '0';
  /* Sort criterion: Content: Nid */
  $handler->display->display_options['sorts']['nid']['id'] = 'nid';
  $handler->display->display_options['sorts']['nid']['table'] = 'node';
  $handler->display->display_options['sorts']['nid']['field'] = 'nid';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'shortcuts';
  $translatables['shortcuts'] = array(
    t('Master'),
    t('Shortcuts'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('Keyword'),
    t('Arguments'),
    t('Title'),
    t('Namespace'),
    t('Tags'),
    t('Page'),
  );
  $export['shortcuts'] = $view;

  return $export;
}
