<?php
/**
 * @file
 * serchilo_features.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function serchilo_features_views_default_views() {
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
  $handler->display->display_options['style_options']['columns'] = array(
    'field_keyword' => 'field_keyword',
    'field_argument_names' => 'field_argument_names',
    'title' => 'title',
    'field_namespace' => 'field_namespace',
    'field_tags' => 'field_tags',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'field_keyword' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_argument_names' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_namespace' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_tags' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
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
  $handler->display->display_options['fields']['field_tags']['separator'] = '';
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
  /* Filter criterion: Content: Keyword (field_keyword) */
  $handler->display->display_options['filters']['field_keyword_value']['id'] = 'field_keyword_value';
  $handler->display->display_options['filters']['field_keyword_value']['table'] = 'field_data_field_keyword';
  $handler->display->display_options['filters']['field_keyword_value']['field'] = 'field_keyword_value';
  $handler->display->display_options['filters']['field_keyword_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_keyword_value']['expose']['operator_id'] = 'keyword_op';
  $handler->display->display_options['filters']['field_keyword_value']['expose']['label'] = 'Keyword';
  $handler->display->display_options['filters']['field_keyword_value']['expose']['use_operator'] = TRUE;
  $handler->display->display_options['filters']['field_keyword_value']['expose']['operator'] = 'field_keyword_value_op';
  $handler->display->display_options['filters']['field_keyword_value']['expose']['identifier'] = 'keyword';
  $handler->display->display_options['filters']['field_keyword_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
  );
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Title';
  $handler->display->display_options['filters']['title']['expose']['use_operator'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
  );
  /* Filter criterion: Content: URL (field_url) */
  $handler->display->display_options['filters']['field_url_value']['id'] = 'field_url_value';
  $handler->display->display_options['filters']['field_url_value']['table'] = 'field_data_field_url';
  $handler->display->display_options['filters']['field_url_value']['field'] = 'field_url_value';
  $handler->display->display_options['filters']['field_url_value']['operator'] = 'contains';
  $handler->display->display_options['filters']['field_url_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_url_value']['expose']['operator_id'] = 'url_op';
  $handler->display->display_options['filters']['field_url_value']['expose']['label'] = 'URL';
  $handler->display->display_options['filters']['field_url_value']['expose']['use_operator'] = TRUE;
  $handler->display->display_options['filters']['field_url_value']['expose']['operator'] = 'field_url_value_op';
  $handler->display->display_options['filters']['field_url_value']['expose']['identifier'] = 'url';
  $handler->display->display_options['filters']['field_url_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
  );
  /* Filter criterion: Content: Namespace (field_namespace) */
  $handler->display->display_options['filters']['field_namespace_tid']['id'] = 'field_namespace_tid';
  $handler->display->display_options['filters']['field_namespace_tid']['table'] = 'field_data_field_namespace';
  $handler->display->display_options['filters']['field_namespace_tid']['field'] = 'field_namespace_tid';
  $handler->display->display_options['filters']['field_namespace_tid']['value'] = '';
  $handler->display->display_options['filters']['field_namespace_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_namespace_tid']['expose']['operator_id'] = 'field_namespace_tid_op';
  $handler->display->display_options['filters']['field_namespace_tid']['expose']['label'] = 'Namespace';
  $handler->display->display_options['filters']['field_namespace_tid']['expose']['operator'] = 'field_namespace_tid_op';
  $handler->display->display_options['filters']['field_namespace_tid']['expose']['identifier'] = 'namespace';
  $handler->display->display_options['filters']['field_namespace_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
  );
  $handler->display->display_options['filters']['field_namespace_tid']['vocabulary'] = 'namespaces';
  /* Filter criterion: Content: Tags (field_tags) */
  $handler->display->display_options['filters']['field_tags_tid']['id'] = 'field_tags_tid';
  $handler->display->display_options['filters']['field_tags_tid']['table'] = 'field_data_field_tags';
  $handler->display->display_options['filters']['field_tags_tid']['field'] = 'field_tags_tid';
  $handler->display->display_options['filters']['field_tags_tid']['value'] = '';
  $handler->display->display_options['filters']['field_tags_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_tags_tid']['expose']['operator_id'] = 'field_tags_tid_op';
  $handler->display->display_options['filters']['field_tags_tid']['expose']['label'] = 'Tags';
  $handler->display->display_options['filters']['field_tags_tid']['expose']['operator'] = 'field_tags_tid_op';
  $handler->display->display_options['filters']['field_tags_tid']['expose']['identifier'] = 'tags';
  $handler->display->display_options['filters']['field_tags_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
  );
  $handler->display->display_options['filters']['field_tags_tid']['vocabulary'] = 'tags';

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
    t('URL'),
    t('Page'),
  );
  $export['shortcuts'] = $view;

  return $export;
}
