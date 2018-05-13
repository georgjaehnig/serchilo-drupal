<?PHP

/**
 * Exports shortcuts and namespaces to the files directory.
 * Creates directories if necessary.
 *
 * @return void
 */
function serchilo_export() {
  system('mkdir -p sites/default/files/serchilo/export');
  serchilo_export_to_json_gz_file('sites/default/files/serchilo/export/serchilo');
}

/**
 * Exports shortcuts and namespaces to a .json.gz file.
 *
 * @param string file_without_suffix
 *   Path to the file, without its suffix, e.g.
 *     /path/to/file
 *   will create
 *     /path/to/file.json.gz
 *
 * @return void
 */
function serchilo_export_to_json_gz_file($file_without_suffix) {

  $export = serchilo_export_shortcuts_and_namespaces();
  $export_json = drupal_json_encode($export);

  file_put_contents($file_without_suffix . '.json', $export_json);
  system('gzip -f ' . $file_without_suffix . '.json');
}

/**
 * Exports shortcuts to Trovu dir.
 *
 * @param string dir
 *   Path to the dir.
 
 * @return void
 */
function serchilo_export_to_json_dir($dir) {

  $codes = array (
    'aw' => 'abw',
    'af' => 'afg',
    'ao' => 'ago',
    'ai' => 'aia',
    'ax' => 'ala',
    'al' => 'alb',
    'ad' => 'and',
    'ae' => 'are',
    'ar' => 'arg',
    'am' => 'arm',
    'as' => 'asm',
    'aq' => 'ata',
    'tf' => 'atf',
    'ag' => 'atg',
    'au' => 'aus',
    'at' => 'aut',
    'az' => 'aze',
    'bi' => 'bdi',
    'be' => 'bel',
    'bj' => 'ben',
    'bq' => 'bes',
    'bf' => 'bfa',
    'bd' => 'bgd',
    'bg' => 'bgr',
    'bh' => 'bhr',
    'bs' => 'bhs',
    'ba' => 'bih',
    'bl' => 'blm',
    'by' => 'blr',
    'bz' => 'blz',
    'bm' => 'bmu',
    'bo' => 'bol',
    'br' => 'bra',
    'bb' => 'brb',
    'bn' => 'brn',
    'bt' => 'btn',
    'bv' => 'bvt',
    'bw' => 'bwa',
    'cf' => 'caf',
    'ca' => 'can',
    'cc' => 'cck',
    'ch' => 'che',
    'cl' => 'chl',
    'cn' => 'chn',
    'ci' => 'civ',
    'cm' => 'cmr',
    'cd' => 'cod',
    'cg' => 'cog',
    'ck' => 'cok',
    'co' => 'col',
    'km' => 'com',
    'cv' => 'cpv',
    'cr' => 'cri',
    'cu' => 'cub',
    'cw' => 'cuw',
    'cx' => 'cxr',
    'ky' => 'cym',
    'cy' => 'cyp',
    'cz' => 'cze',
    'de' => 'deu',
    'dj' => 'dji',
    'dm' => 'dma',
    'dk' => 'dnk',
    'do' => 'dom',
    'dz' => 'dza',
    'ec' => 'ecu',
    'eg' => 'egy',
    'er' => 'eri',
    'eh' => 'esh',
    'es' => 'esp',
    'ee' => 'est',
    'et' => 'eth',
    'fi' => 'fin',
    'fj' => 'fji',
    'fk' => 'flk',
    'fr' => 'fra',
    'fo' => 'fro',
    'fm' => 'fsm',
    'ga' => 'gab',
    'gb' => 'gbr',
    'ge' => 'geo',
    'gg' => 'ggy',
    'gh' => 'gha',
    'gi' => 'gib',
    'gn' => 'gin',
    'gp' => 'glp',
    'gm' => 'gmb',
    'gw' => 'gnb',
    'gq' => 'gnq',
    'gr' => 'grc',
    'gd' => 'grd',
    'gl' => 'grl',
    'gt' => 'gtm',
    'gf' => 'guf',
    'gu' => 'gum',
    'gy' => 'guy',
    'hk' => 'hkg',
    'hm' => 'hmd',
    'hn' => 'hnd',
    'hr' => 'hrv',
    'ht' => 'hti',
    'hu' => 'hun',
    'id' => 'idn',
    'im' => 'imn',
    'in' => 'ind',
    'io' => 'iot',
    'ie' => 'irl',
    'ir' => 'irn',
    'iq' => 'irq',
    'is' => 'isl',
    'il' => 'isr',
    'it' => 'ita',
    'jm' => 'jam',
    'je' => 'jey',
    'jo' => 'jor',
    'jp' => 'jpn',
    'kz' => 'kaz',
    'ke' => 'ken',
    'kg' => 'kgz',
    'kh' => 'khm',
    'ki' => 'kir',
    'kn' => 'kna',
    'kr' => 'kor',
    'kw' => 'kwt',
    'la' => 'lao',
    'lb' => 'lbn',
    'lr' => 'lbr',
    'ly' => 'lby',
    'lc' => 'lca',
    'li' => 'lie',
    'lk' => 'lka',
    'ls' => 'lso',
    'lt' => 'ltu',
    'lu' => 'lux',
    'lv' => 'lva',
    'mo' => 'mac',
    'mf' => 'maf',
    'ma' => 'mar',
    'mc' => 'mco',
    'md' => 'mda',
    'mg' => 'mdg',
    'mv' => 'mdv',
    'mx' => 'mex',
    'mh' => 'mhl',
    'mk' => 'mkd',
    'ml' => 'mli',
    'mt' => 'mlt',
    'mm' => 'mmr',
    'me' => 'mne',
    'mn' => 'mng',
    'mp' => 'mnp',
    'mz' => 'moz',
    'mr' => 'mrt',
    'ms' => 'msr',
    'mq' => 'mtq',
    'mu' => 'mus',
    'mw' => 'mwi',
    'my' => 'mys',
    'yt' => 'myt',
    'na' => 'nam',
    'nc' => 'ncl',
    'ne' => 'ner',
    'nf' => 'nfk',
    'ng' => 'nga',
    'ni' => 'nic',
    'nu' => 'niu',
    'nl' => 'nld',
    'no' => 'nor',
    'np' => 'npl',
    'nr' => 'nru',
    'nz' => 'nzl',
    'om' => 'omn',
    'pk' => 'pak',
    'pa' => 'pan',
    'pn' => 'pcn',
    'pe' => 'per',
    'ph' => 'phl',
    'pw' => 'plw',
    'pg' => 'png',
    'pl' => 'pol',
    'pr' => 'pri',
    'kp' => 'prk',
    'pt' => 'prt',
    'py' => 'pry',
    'ps' => 'pse',
    'pf' => 'pyf',
    'qa' => 'qat',
    're' => 'reu',
    'ro' => 'rou',
    'ru' => 'rus',
    'rw' => 'rwa',
    'sa' => 'sau',
    'sd' => 'sdn',
    'sn' => 'sen',
    'sg' => 'sgp',
    'gs' => 'sgs',
    'sh' => 'shn',
    'sj' => 'sjm',
    'sb' => 'slb',
    'sl' => 'sle',
    'sv' => 'slv',
    'sm' => 'smr',
    'so' => 'som',
    'pm' => 'spm',
    'rs' => 'srb',
    'ss' => 'ssd',
    'st' => 'stp',
    'sr' => 'sur',
    'sk' => 'svk',
    'si' => 'svn',
    'se' => 'swe',
    'sz' => 'swz',
    'sx' => 'sxm',
    'sc' => 'syc',
    'sy' => 'syr',
    'tc' => 'tca',
    'td' => 'tcd',
    'tg' => 'tgo',
    'th' => 'tha',
    'tj' => 'tjk',
    'tk' => 'tkl',
    'tm' => 'tkm',
    'tl' => 'tls',
    'to' => 'ton',
    'tt' => 'tto',
    'tn' => 'tun',
    'tr' => 'tur',
    'tv' => 'tuv',
    'tw' => 'twn',
    'tz' => 'tza',
    'ug' => 'uga',
    'ua' => 'ukr',
    'um' => 'umi',
    'uy' => 'ury',
    'us' => 'usa',
    'uz' => 'uzb',
    'va' => 'vat',
    'vc' => 'vct',
    've' => 'ven',
    'vg' => 'vgb',
    'vi' => 'vir',
    'vn' => 'vnm',
    'vu' => 'vut',
    'wf' => 'wlf',
    'ws' => 'wsm',
    'ye' => 'yem',
    'za' => 'zaf',
    'zm' => 'zmb',
    'zw' => 'zwe',
  );

  $codes3to2 = array_flip($codes);

  $shortcuts = serchilo_export_shortcuts();
  foreach ($shortcuts as $shortcut) {

    $trovu_dir = 'trovu';
    if ('old-' == substr($shortcut['namespace'], 0, 4)) {
      $trovu_dir = 'trovu-old';
    }
    elseif (strlen($shortcut['namespace']) >= 4) {
      $trovu_dir = 'trovu-user';
    }
    elseif (strlen($shortcut['namespace']) == 3) {
      $shortcut['namespace'] = '.' . $codes3to2[$shortcut['namespace']];
    }
    
    $keyword_dir = $dir . '/' . $trovu_dir . '/shortcuts/' . rawurlencode($shortcut['namespace']) . '/' . rawurlencode($shortcut['keyword']) . '/';

    system('mkdir -p ' .  $keyword_dir);

    $call = array();
    $call['url'] = $shortcut['url'];

    $post_parameters = serchilo_get_post_parameters($shortcut['post_parameters']);
    // Only add $post_parameters if not empty.
    if (!empty($post_parameters)) {
      $call['post_parameters'] = $post_parameters;
    }

    $more = array();
    $more['title'] = $shortcut['title'];
    $more['description'] = $shortcut['description'];
    $more['tags'] = $shortcut['tags'];
    $more['examples'] = $shortcut['examples'];
    $more['tests'] = $shortcut['test'];

    $call_json = json_encode($call, JSON_PRETTY_PRINT | JSON_UNESCAPED_SLASHES | JSON_UNESCAPED_UNICODE | JSON_NUMERIC_CHECK);
    $more_json = json_encode($more, JSON_PRETTY_PRINT | JSON_UNESCAPED_SLASHES | JSON_UNESCAPED_UNICODE | JSON_NUMERIC_CHECK);

    $argumentCount = count(serchilo_get_argument_names($shortcut['url'], ($shortcut['post_parameters'])));

    $call_path = $keyword_dir . $argumentCount . '.call.json';
    $more_path = $keyword_dir . $argumentCount . '.more.json';

    file_put_contents($call_path, $call_json);
    file_put_contents($more_path, $more_json);
  }
}

/**
 * Exports the shortcuts and the namespaces.
 *
 * @return array $export
 *   Two-item array containing the 
 *   - shortcuts and the
 *   - namespaces 
 */
function serchilo_export_shortcuts_and_namespaces() {

  $export['shortcuts']  = serchilo_export_shortcuts();
  $export['namespaces'] = serchilo_export_namespaces();

  return $export;
}

/**
 * Exports the shortcuts.
 *
 * @return array $exported_namespaces 
 *   Array containing namespaces with
 *   - id
 *   - title
 *   - description
 *   - url
 *   - keyword
 *   - argument_names (array)
 *   - set_referrer
 *   - invisible
 *   - namespace
 *   - tags (array)
 *   - examples, array of two-item array containing
 *     - arguments (as string separated by comma)
 *     - description
 */
function serchilo_export_shortcuts() {

  $efq = new EntityFieldQuery;

  $result = $efq
    ->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'shortcut')
    ->propertyCondition('status', NODE_PUBLISHED)
    ->execute();

  $nids = array_keys(array_shift($result));

  $exported_shortcuts = array();

  foreach ($nids as $nid) {

    $node = node_load($nid);

    $namespace = taxonomy_term_load($node->field_namespace[LANGUAGE_NONE][0]['tid']);

    $exported_shortcut['id']              = $node->nid;
    $exported_shortcut['title']           = $node->title;
    $exported_shortcut['description']     = (string) drupal_array_get_nested_value($node->field_description,     array(LANGUAGE_NONE, 0, 'value'));
    $exported_shortcut['url']             = (string) drupal_array_get_nested_value($node->field_url,             array(LANGUAGE_NONE, 0, 'value'));
    $exported_shortcut['keyword']         = (string) drupal_array_get_nested_value($node->field_keyword,         array(LANGUAGE_NONE, 0, 'value'));
    $exported_shortcut['argument_names']  = (string) drupal_array_get_nested_value($node->field_argument_names,  array(LANGUAGE_NONE, 0, 'value'));
    $exported_shortcut['set_referrer']    = (string) drupal_array_get_nested_value($node->field_set_referrer,    array(LANGUAGE_NONE, 0, 'value'));
    $exported_shortcut['invisible']       = (string) drupal_array_get_nested_value($node->field_invisible,       array(LANGUAGE_NONE, 0, 'value'));
    $exported_shortcut['post_parameters'] = (string) drupal_array_get_nested_value($node->field_post_parameters, array(LANGUAGE_NONE, 0, 'value'));

    $wnode = entity_metadata_wrapper('node', $node);

    $exported_shortcut['namespace']      = $wnode->field_namespace->value()->name;
    $exported_shortcut['tags']           = array_map(function ($tag) { return $tag->name; }, $wnode->field_tags->value() ?: array() );

    $exported_shortcut['examples']       = array();
    foreach ($wnode->field_example as $example) {
      $exported_shortcut['examples'][$example->field_example_arguments->value()] = $example->field_example_description->value();
    }

    $exported_shortcut['test']       = array();
    foreach ($wnode->field_test as $test) {
      $exported_shortcut['test'][$test->field_test_arguments->value()] = $test->field_test_expected_content->value();
    }

    $exported_shortcuts[] = $exported_shortcut;
  }

  return $exported_shortcuts;
}

/**
 * Exports the namespaces.
 *
 * @return array $exported_namespaces 
 *   Array containing namespaces with
 *   * title
 *   * description
 *   * (namespace) type
 */
function serchilo_export_namespaces() {

  $vocabularies = taxonomy_vocabulary_get_names();

  $efq = new EntityFieldQuery;
  $result = $efq
    ->entityCondition('entity_type', 'taxonomy_term')
    ->propertyCondition('vid', $vocabularies['namespaces']->vid )
    ->execute();

  $namespace_ids = array_keys(array_shift($result));
  $exported_namespaces = array();

  foreach ($namespace_ids as $namespace_id) {

    $term = taxonomy_term_load($namespace_id);
    $wterm = entity_metadata_wrapper('taxonomy_term', $term);

    $exported_namespace['tid']        = $wterm->tid->value();
    $exported_namespace['name']        = $wterm->name->value();
    $exported_namespace['description'] = $wterm->description->raw();
    $exported_namespace['type']        = $wterm->field_namespace_type->value()->name;

    $exported_namespaces[] = $exported_namespace;
  }

  return $exported_namespaces;
}
