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
function serchilo_telegram_process($env) {

  $telegram = new Telegram(SERCHILO_TELEGRAM_BOT_TOKEN, 'FindFindBot');
  $telegram->addCommandsPath(__DIR__ . '/telegram/Commands/');
  $telegram->setCommandConfig('Genericmessage', ['env' => $env]);
  $telegram->setCommandConfig('inlinequery', ['env' => $env]);

  $telegram->handle();
}

function serchilo_telegram_get_settings(&$env, $telegram_user_id) {


  if ($env['user_id'] = serchilo_get_values_from_table('serchilo_telegram_users', 'telegram_user_id', $telegram_user_id, 'uid')[0]) {
    $env['call_type'] = 'u';
    $env['user_name'] = serchilo_get_values_from_table('users', 'uid', $env['user_id'], 'name')[0];
  } else if ($namespaces_path = serchilo_get_values_from_table('serchilo_telegram_users', 'telegram_user_id', $telegram_user_id, 'namespaces_path')[0]) {
    $env['call_type'] = 'n';
    // TODO: Refactor as serchilo_namespace_names_tonamespaces_path().
    $env['namespace_names'] = explode('.', $namespaces_path);
    array_unshift($env['namespace_names'], SERCHILO_PLANET_NAMESPACE);
  }
  serchilo_populate_environment($env);
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
