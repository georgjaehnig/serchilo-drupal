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


function serchilo_convert_php_date_to_momentjs($str) {

  // Based on:
  // https://gist.github.com/NTICompass/9375143
  $map = array(
    'd' => 'DD',
    'D' => 'ddd',
    'j' => 'D',
    'l' => 'dddd',
    'N' => 'E',
    'w' => 'd',
    'W' => 'W',
    'F' => 'MMMM',
    'm' => 'MM',
    'M' => 'MMM',
    'n' => 'M',
    'o' => 'GGGG',
    'Y' => 'YYYY',
    'y' => 'YY',
    'a' => 'a',
    'A' => 'A',
    'g' => 'h',
    'G' => 'H',
    'h' => 'hh',
    'H' => 'HH',
    'i' => 'mm',
    's' => 'ss',
    'O' => 'ZZ',
    'P' => 'Z',
    'U' => 'X',
  );

  $str = strtr($str, $map);

  return $str;
}


function serchilo_convert_3letter_to_2letter($code3letter) {

  $codes=array('aw'=>'abw','af'=>'afg','ao'=>'ago','ai'=>'aia','ax'=>'ala','al'=>'alb','ad'=>'and','ae'=>'are','ar'=>'arg','am'=>'arm','as'=>'asm','aq'=>'ata','tf'=>'atf','ag'=>'atg','au'=>'aus','at'=>'aut','az'=>'aze','bi'=>'bdi','be'=>'bel','bj'=>'ben','bq'=>'bes','bf'=>'bfa','bd'=>'bgd','bg'=>'bgr','bh'=>'bhr','bs'=>'bhs','ba'=>'bih','bl'=>'blm','by'=>'blr','bz'=>'blz','bm'=>'bmu','bo'=>'bol','br'=>'bra','bb'=>'brb','bn'=>'brn','bt'=>'btn','bv'=>'bvt','bw'=>'bwa','cf'=>'caf','ca'=>'can','cc'=>'cck','ch'=>'che','cl'=>'chl','cn'=>'chn','ci'=>'civ','cm'=>'cmr','cd'=>'cod','cg'=>'cog','ck'=>'cok','co'=>'col','km'=>'com','cv'=>'cpv','cr'=>'cri','cu'=>'cub','cw'=>'cuw','cx'=>'cxr','ky'=>'cym','cy'=>'cyp','cz'=>'cze','de'=>'deu','dj'=>'dji','dm'=>'dma','dk'=>'dnk','do'=>'dom','dz'=>'dza','ec'=>'ecu','eg'=>'egy','er'=>'eri','eh'=>'esh','es'=>'esp','ee'=>'est','et'=>'eth','fi'=>'fin','fj'=>'fji','fk'=>'flk','fr'=>'fra','fo'=>'fro','fm'=>'fsm','ga'=>'gab','gb'=>'gbr','ge'=>'geo','gg'=>'ggy','gh'=>'gha','gi'=>'gib','gn'=>'gin','gp'=>'glp','gm'=>'gmb','gw'=>'gnb','gq'=>'gnq','gr'=>'grc','gd'=>'grd','gl'=>'grl','gt'=>'gtm','gf'=>'guf','gu'=>'gum','gy'=>'guy','hk'=>'hkg','hm'=>'hmd','hn'=>'hnd','hr'=>'hrv','ht'=>'hti','hu'=>'hun','id'=>'idn','im'=>'imn','in'=>'ind','io'=>'iot','ie'=>'irl','ir'=>'irn','iq'=>'irq','is'=>'isl','il'=>'isr','it'=>'ita','jm'=>'jam','je'=>'jey','jo'=>'jor','jp'=>'jpn','kz'=>'kaz','ke'=>'ken','kg'=>'kgz','kh'=>'khm','ki'=>'kir','kn'=>'kna','kr'=>'kor','kw'=>'kwt','la'=>'lao','lb'=>'lbn','lr'=>'lbr','ly'=>'lby','lc'=>'lca','li'=>'lie','lk'=>'lka','ls'=>'lso','lt'=>'ltu','lu'=>'lux','lv'=>'lva','mo'=>'mac','mf'=>'maf','ma'=>'mar','mc'=>'mco','md'=>'mda','mg'=>'mdg','mv'=>'mdv','mx'=>'mex','mh'=>'mhl','mk'=>'mkd','ml'=>'mli','mt'=>'mlt','mm'=>'mmr','me'=>'mne','mn'=>'mng','mp'=>'mnp','mz'=>'moz','mr'=>'mrt','ms'=>'msr','mq'=>'mtq','mu'=>'mus','mw'=>'mwi','my'=>'mys','yt'=>'myt','na'=>'nam','nc'=>'ncl','ne'=>'ner','nf'=>'nfk','ng'=>'nga','ni'=>'nic','nu'=>'niu','nl'=>'nld','no'=>'nor','np'=>'npl','nr'=>'nru','nz'=>'nzl','om'=>'omn','pk'=>'pak','pa'=>'pan','pn'=>'pcn','pe'=>'per','ph'=>'phl','pw'=>'plw','pg'=>'png','pl'=>'pol','pr'=>'pri','kp'=>'prk','pt'=>'prt','py'=>'pry','ps'=>'pse','pf'=>'pyf','qa'=>'qat','re'=>'reu','ro'=>'rou','ru'=>'rus','rw'=>'rwa','sa'=>'sau','sd'=>'sdn','sn'=>'sen','sg'=>'sgp','gs'=>'sgs','sh'=>'shn','sj'=>'sjm','sb'=>'slb','sl'=>'sle','sv'=>'slv','sm'=>'smr','so'=>'som','pm'=>'spm','rs'=>'srb','ss'=>'ssd','st'=>'stp','sr'=>'sur','sk'=>'svk','si'=>'svn','se'=>'swe','sz'=>'swz','sx'=>'sxm','sc'=>'syc','sy'=>'syr','tc'=>'tca','td'=>'tcd','tg'=>'tgo','th'=>'tha','tj'=>'tjk','tk'=>'tkl','tm'=>'tkm','tl'=>'tls','to'=>'ton','tt'=>'tto','tn'=>'tun','tr'=>'tur','tv'=>'tuv','tw'=>'twn','tz'=>'tza','ug'=>'uga','ua'=>'ukr','um'=>'umi','uy'=>'ury','us'=>'usa','uz'=>'uzb','va'=>'vat','vc'=>'vct','ve'=>'ven','vg'=>'vgb','vi'=>'vir','vn'=>'vnm','vu'=>'vut','wf'=>'wlf','ws'=>'wsm','ye'=>'yem','za'=>'zaf','zm'=>'zmb','zw'=>'zwe');

  $codes3to2 = array_flip($codes);

  $code2letter = $codes3to2[$code3letter];

  return $code2letter;
}

/**
 * Check if shortcut is a user shortcut.
 *
 * @param string namespace
 *   Namespace name
 * @return void
 */
function serchilo_is_user_shortcut($namespace) {

  // Begins with 'old-': site shortcut.
  if ('old-' == substr($namespace, 0, 4)) {
    return FALSE;
  }
  // Longer or equal than 4: user shortcut.
  if (strlen($namespace) >= 4) {
    return TRUE;
  }
  // Rest: site shortcut.
  return FALSE;
}

function serchilo_custom_namespaces_to_str($items) {

  $namespaces = [];

  if (empty($items)) {
    return $namespaces;
  }

  foreach ($items as $item) {
    $term = taxonomy_term_load($item['tid']);
    $namespace = $term->name;
    if (strlen($term->name) == 3) {
      $namespace = '.' . serchilo_convert_3letter_to_2letter($term->name);
    }
    $namespaces[] = $namespace;
  }
  return $namespaces;
}


function serchilo_export_to_trovu_user_settings($export_dir) {

  $users = entity_load('user');

  foreach ($users as $account) {

    // Omit anonymous user.
    if (empty($account->name)) {
      continue;
    }

    $dir = $export_dir . '/users/' .  $account->name;

    // Filter out users without actual settings.
    $no_custom_namespaces = (empty($account->field_custom_namespaces[LANGUAGE_NONE]));
    $no_default_keyword = (empty($account->field_default_keyword[LANGUAGE_NONE][0]));
    $mail_in_default_keyword = (strpos(serchilo_array_value($account->field_default_keyword[LANGUAGE_NONE][0], 'value'), '@')  !== false);
    $username_in_custom_namespaces = ([$account->name] == serchilo_custom_namespaces_to_str($account->field_custom_namespaces[LANGUAGE_NONE]));
    $no_user_shortcuts = (!file_exists($dir));

    //if (($no_custom_namespaces && $no_default_keyword && $no_user_shortcuts) || $mail_in_default_keyword || $username_in_custom_namespaces) {
    if ((($no_custom_namespaces || $username_in_custom_namespaces) && $no_default_keyword && $no_user_shortcuts) || $mail_in_default_keyword) {
      continue; 
      /*
      echo $account->name . ":";
      echo $no_custom_namespaces . ":";
      echo $no_default_keyword . ":";
      echo $no_user_shortcuts . ":";
      echo $mail_in_default_keyword . ":";
      echo $username_in_custom_namespaces . ":";
      echo "\n";
      echo $account->name . "\n";
      print_r($account->field_default_keyword);
      print_r($account->field_custom_namespaces);
       */
    }
    //print_r($account->field_default_keyword);
    //print_r($account->field_custom_namespaces);

    $config = [];

    // List all subscribed namespaces.
    $config['namespaces'] = ['o'];

    if ($value = serchilo_array_value($account->field_default_keyword[LANGUAGE_NONE][0], 'value')) {
      $config['defaultKeyword'] = $value;
    }
    if ($tid = serchilo_array_value($account->field_language_namespace[LANGUAGE_NONE][0], 'tid')) {
      $term = taxonomy_term_load($tid);
      $config['language'] = $term->name;
      $config['namespaces'][] = $term->name;
    }
    if ($tid = serchilo_array_value($account->field_country_namespace[LANGUAGE_NONE][0], 'tid')) {
      $term = taxonomy_term_load($tid);
      $config['country'] = serchilo_convert_3letter_to_2letter($term->name);
      $config['namespaces'][] = '.' . serchilo_convert_3letter_to_2letter($term->name);
    }
    if (!empty($account->field_custom_namespaces[LANGUAGE_NONE])) {
      $config['namespaces'] = array_merge(
        $config['namespaces'],
        serchilo_custom_namespaces_to_str($account->field_custom_namespaces[LANGUAGE_NONE])
      );
    }
    
    // Also set the user namespace in the list.
    $user_namespace = [
      'github' => '.',
      'name' => $account->name,
    ];
    $config['namespaces'][] = $user_namespace;

    $config_yaml = yaml_emit($config, YAML_UTF8_ENCODING);
    $config_yaml = substr($config_yaml, 4);
    $config_yaml = substr($config_yaml, 0, -4);

    if (!file_exists($dir)) {
      mkdir($dir, 0777, true);
    }

    file_put_contents($dir . '/config.yml', $config_yaml);

    // Zip user dir.
    system("(cd $dir && zip -q -r - .) > $dir.zip");

    // Delete user dir.
    system("rm -r $dir");
  }
}

function serchilo_export_to_trovu_shortcuts($export_dir) {

  $shortcuts = serchilo_export_shortcuts();
  $shortcutsByNamespace = [];
  foreach ($shortcuts as $shortcut) {

    if (!$shortcut['approved']) {
      echo "Not approved: \thttps://www.findfind.it/shortcuts/" . $shortcut['id'] . "\n";
      continue;
    }
    if (!$shortcut['active']) {
      echo "Not active: \thttps://www.findfind.it/shortcuts/" . $shortcut['id'] . "\n";
      continue;
    }
    if ($shortcut['invisible']) {
      echo "Invisible: \thttps://www.findfind.it/shortcuts/" . $shortcut['id'] . "\n";
      continue;
    }

    // For site namespaces:
    if (!serchilo_is_user_shortcut($shortcut['namespace'])) {
      // Omit those to findfind.it.
      if (preg_match('~^/~', $shortcut['url'])) {
        echo $shortcut['url'] . "\n";
        continue;
      }
      if (preg_match('~findfind.it~', $shortcut['url'])) {
        echo $shortcut['url'] . "\n";
        continue;
      }
    }

    list($key, $namespace, $export) = serchilo_export_to_trovu_shortcut($shortcut);
    $shortcutsByNamespace[$namespace][$key] = $export;
  }
  //print_r($shortcutsByNamespace);
  //return;

  foreach($shortcutsByNamespace as $namespace=>$shortcuts) {

    ksort($shortcuts);

    $export = $shortcuts;

    $export_yaml = yaml_emit($export, YAML_UTF8_ENCODING);
    $export_yaml = substr($export_yaml, 4);
    $export_yaml = substr($export_yaml, 0, -4);

    // Set correct dir.
    if (serchilo_is_user_shortcut($namespace)) {
      $shortcut_dir = 'users/' . $namespace;
      $shortcut_file = 'shortcuts.yml';
    }
    else {
      $shortcut_dir = 'trovu-data/shortcuts';
      $shortcut_file = $namespace . '.yml';
    }

    $dir = $export_dir . '/' . $shortcut_dir;

    if (!file_exists($dir)) {
      mkdir($dir, 0777, true);
    }

    $export_path = $dir . '/' . $shortcut_file;

    //echo $export_path . "\n";
    file_put_contents($export_path, $export_yaml);
  }
}

function serchilo_export_to_trovu_shortcut($shortcut) {

  // Convert output attribute from PHP's date() format to momentjs.
  $arguments = serchilo_get_arguments_from_string($shortcut['url']) ?? [];
  $variables = serchilo_get_variables_from_string($shortcut['url']) ?? [];

  $argumentCount = count(serchilo_get_argument_names($shortcut['url'], ($shortcut['post_parameters'])));

  foreach (array_merge($arguments, $variables) as $name=>$placeholders) {
    foreach ($placeholders as $match=>$attributes) {
      if (!empty($attributes['output'])) {
        $attributes['output'] = serchilo_convert_php_date_to_momentjs($attributes['output']);
      }
      //array_walk($attributes, function(&$v, $k) { $v =  $k . '=' . $v; });
      //$prefix = substr($match, 0, 2);
      //$match_replaced_custom = $prefix . $name . '|' . join('|', $attributes) . '}';
      $match_replaced_yaml = '<';
      if ($match[1] == '$') {
      $match_replaced_yaml .= '$';
      }
      $match_replaced_yaml .= $name;
      if (!empty($attributes)) {
        $match_replaced_yaml .= ': {';
        foreach ($attributes as $k=>$v) {
          $match_replaced_yaml .= "$k: $v, ";
        }
        $match_replaced_yaml = substr($match_replaced_yaml, 0, -2);
        $match_replaced_yaml .= '}';
      }
      $match_replaced_yaml .= '>';
      //watchdog(WATCHDOG_DEBUG, '4'.htmlspecialchars($match_replaced_yaml));
      $shortcut['url'] = str_replace($match, $match_replaced_yaml, $shortcut['url']);
    }
  }

  $export = array();
  $export['url'] = $shortcut['url'];

  $post_parameters = serchilo_get_post_parameters($shortcut['post_parameters']);
  foreach ($post_parameters as $key=>$value) {
    $export['post parameters'][$key] = $value;
  }

  foreach(['title', 'description', 'tags', 'examples', 'tests'] as $k) {
    if (!empty($shortcut[$k])) {
      $export[$k] = $shortcut[$k];
    }
  }

  $key = $shortcut['keyword'] . ' ' . $argumentCount;

  $namespace = $shortcut['namespace'];
  if (strlen($shortcut['namespace']) == 3) {
    $namespace = '.' . serchilo_convert_3letter_to_2letter($shortcut['namespace']);
  }

  return array($key, $namespace, $export);

}

/**
 * Exports shortcuts to Trovu dir.
 *
 * @param string dir
 *   Path to the dir.
 * @return void
 */
function serchilo_export_to_trovu($export_dir) {

  echo "Exporting shortcuts...\n";
  serchilo_export_to_trovu_shortcuts($export_dir);

  //echo "Exporting user data...\n";
  //serchilo_export_to_trovu_user_settings($export_dir);
}

function serchilo_replace_trovu_path_tokens($str, $namespace, $keyword, $argumentCount) {

  $str = strtr(
    $str,
    array(
      '{%namespace}' => $namespace,
      '{%keyword}' => $keyword,
      '{%argumentCount}' => $argumentCount,
    )
  );

  return $str;
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
    $exported_shortcut['active']          = (bool)   drupal_array_get_nested_value($node->field_active,          array(LANGUAGE_NONE, 0, 'value'));
    $exported_shortcut['approved']        = (bool)   drupal_array_get_nested_value($node->field_approved,        array(LANGUAGE_NONE, 0, 'value'));

    foreach(['title', 'description', 'url', 'keyword', 'argument_names', 'post_parameters'] as $k) {
      $exported_shortcut[$k] = trim($exported_shortcut[$k]);
    }

    $wnode = entity_metadata_wrapper('node', $node);

    $exported_shortcut['namespace']      = $wnode->field_namespace->value()->name;
    $exported_shortcut['tags']           = array_map(function ($tag) { return $tag->name; }, $wnode->field_tags->value() ?: array() );

    $exported_shortcut['examples']       = array();
    foreach ($wnode->field_example as $example) {
      if (empty($example->field_example_arguments->value())) {
        continue;
      }
      $exported_shortcut['examples'][$example->field_example_arguments->value()] = $example->field_example_description->value();
    }

    $exported_shortcut['test']       = array();
    foreach ($wnode->field_test as $test) {
      if (empty($test->field_test_arguments->value())) {
        continue;
      }
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
