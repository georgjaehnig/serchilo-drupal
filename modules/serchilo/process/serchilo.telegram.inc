<?PHP

require '../../../vendor/autoload.php';

use Telegram\Bot\Api;
use Serchilo\Telegram\Bot\Commands;
use Longman\TelegramBot\Telegram;
use Longman\TelegramBot\Request;

/**
 * Create a Telegram API object.
 *
 * @param array $env
 *   The environment, holding all relevant data of the request.
 */
function serchilo_telegram_test_new($env) {

  $telegram = new Telegram(SERCHILO_TELEGRAM_BOT_TOKEN, 'FindFindBot');
  $telegram->addCommandsPath(__DIR__ . '/telegram/Commands/');
  $telegram->setCommandConfig('Genericmessage', ['env' => $env]);
  $telegram->setCommandConfig('inlinequery', ['env' => $env]);

  $r = $telegram->handle();
  //error_log(json_encode('i'));
  error_log(json_encode($r));


  //$response = Request::getUpdates();
  //return $telegram;
}

function serchilo_telegram_get_settings(&$env, $telegram_user_id) {

  //serchilo_get_values_from_table('serchilo_telegram_users')
  //serchilo_get_values_from_table($table, $where_column_name, $where_value, $value_column_name) {
   
  $env['namespace_names'] = array('o', 'de', 'deu');
  $env['call_type'] = 'n';
  serchilo_populate_environment($env);

  /*
  $env['language_namespace_name'] = 'de';
  $env['country_namespace_name'] = 'deu';
  $env['namespace_ids'] = array(465, 151, 154);
  $env['timezone'] = serchilo_get_timezone($env);
   */
}

function serchilo_telegram_remove_settings($telegram_user_id) {

  global $mysqli;

  // Delete current user settings.
  $sql = "
    DELETE
    FROM serchilo_telegram_users
    WHERE
    telegram_user_id  = '" . $mysqli->real_escape_string($telegram_user_id) . "' 
  ";

  $result = $mysqli->query($sql);
}

function serchilo_telegram_set_settings($telegram_user_id, $namespaces_path = NULL, $uid = NULL) {

  global $mysqli;

  // Set new user settings.
  $sql = "
    INSERT INTO 
      serchilo_telegram_users
      (
        telegram_user_id,
        uid,
        namespaces_path
      )
      VALUES (
        :telegram_user_id, 
        :uid, 
        :namespaces_path
      );
  ";

  $sql = serchilo_replace_sql_arguments(
    $mysqli, 
    $sql,
    array(
      'telegram_user_id'  => $telegram_user_id,
      'uid'               => $uid,
      'namespaces_path'   => $namespaces_path,
    )
  );

  $result = $mysqli->query($sql);
}


/**
 * Create a Telegram API object.
 *
 * @param array $env
 *   The environment, holding all relevant data of the request.
 */
function serchilo_telegram_create_api($env) {

  $telegram = new Api(SERCHILO_TELEGRAM_BOT_TOKEN);
  return $telegram;
}

/**
 */
function serchilo_telegram_create_commands($telegram) {

  $telegram->addCommands(array(
    Serchilo\Telegram\Commands\StartCommand::class,
    Serchilo\Telegram\Commands\HelpCommand::class,
  ));
}

/**
 * Check if message is a command.
 *
 * @param object $message
 *   The Telegram message object.
 */
function serchilo_telegram_message_is_command($message) {

  if (empty( $message->getEntities())) {
    return FALSE; 
  }
  $entities = $message->getEntities()->getRawResponse();
  foreach ($entities as $entity) {
    if ('bot_command' == $entity['type']) {
      return TRUE; 
    }
  }
  return FALSE;
}

/**
 * Populate the environment based on Telegram input.
 *
 * @param array $env
 *   The environment, holding all relevant data of the request.
 * @param object $telegram
 *   The Telegram API object.
 */
function serchilo_telegram_populate_environment(&$env, $telegram) {

  $update = $telegram->getWebhookUpdates();

  // If query comes per message:
  if ($message = $update->getMessage()) {
    $env['query'] = $message->getText();
    $env['telegram'] = array();
    $env['telegram']['chat'] = array();
    $env['telegram']['chat']['id'] = $message->getChat()->getId();
    if (serchilo_telegram_message_is_command($message)) {
      $env['telegram']['type'] = 'bot_command';
    } else {
      $env['telegram']['type'] = 'message';
    }
  }

  // If query comes per inline:
  if ($inline_query = $update->getInlineQuery()) {
    $env['query'] = $inline_query->getQuery();
    $env['telegram']['inline_query']['id'] = $inline_query->getId();
    $env['telegram']['type'] = 'inline_query';
  }

    $env = serchilo_parse_query($env['query']) + $env;

    // TODO: Copied this from 
    // serchilo_populate_environment(&$env)
    // case SERCHILO_NAMESPACES_PATH_AFFIX:
    // Needs to be refactored.

    // Add extra_namespace to namespace_names.
    if (!empty($env['extra_namespace_name'])) {
      $env['namespace_names'][] = $env['extra_namespace_name'];
    }
    // Get namespace_ids from namespace_names.
    $env['namespace_ids'] = array_map('serchilo_get_namespace_id', $env['namespace_names']);
}

/**
 * Respond to a Telegram query.
 *
 * @param array $env
 *   The environment, holding all relevant data of the request.
 * @param object $telegram
 *   The environment, holding all relevant data of the request.
 * @return mixed $output
 *   The data to output.
 */
function serchilo_telegram_respond(&$env, $telegram, $output) {

  if ($output['status']['found']) {
    $url = $output['url']['final'];
    serchilo_log_shortcut_call($output['#shortcut'], $env, $output['status']['default_keyword_used']);
  } else {
    $text = 'Error: No shortcut found.';
  }

  switch ($env['telegram']['type']) {
  case 'message':
    $response = $telegram->sendMessage([
      'chat_id' => $env['telegram']['chat']['id'],
      'text' => (!empty($url) ? $url : $text),
      //'text' => var_export($env, TRUE),
    ]);
    break;
  case 'inline_query':
    if (empty($url)) {
      break;
    }
    $results = array();
    $results[] = array(
      'type' => 'article',
      'id' => '0',
      'title' => $output['#shortcut']['title'],
      'input_message_content' => array(
        'message_text' => $env['query'] . ' → ' . $url,
      ),
      'url' => $url,
    );
    $params = array(
      'inline_query_id' => $env['telegram']['inline_query']['id'],
      'results' => $results,
    );
    $telegram->answerInlineQuery($params);
    break;
  }
}
