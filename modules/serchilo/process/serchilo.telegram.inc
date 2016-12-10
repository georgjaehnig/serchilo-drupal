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
