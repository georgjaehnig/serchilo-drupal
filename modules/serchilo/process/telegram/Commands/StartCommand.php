<?php

namespace Longman\TelegramBot\Commands\SystemCommands;

use Longman\TelegramBot\Commands\SystemCommand;
use Longman\TelegramBot\Request;

/**
 * Start command
 */
class StartCommand extends SystemCommand
{
    /**#@+
     * {@inheritdoc}
     */
    protected $name = 'start';
    protected $description = '(Re)Start the FindFindBot with defaults.';
    protected $usage = '/start';
    protected $version = '1.0.1';
    protected $need_mysql = false;
    /**#@-*/

    /**
     * {@inheritdoc}
     */
    public function execute()
    {
        global $mysqli;

        $telegram_user_id = $this->getUpdate()->getMessage()->getFrom()->getId();

        // Delete current user settings.
        $sql = "
          DELETE
          FROM serchilo_telegram_users
          WHERE
          telegram_user_id  = '" . $mysqli->real_escape_string($telegram_user_id) . "' 
        ";

        $result = $mysqli->query($sql);

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

        $namespaces_path = SERCHILO_DEFAULT_LANGUAGE . '.' . SERCHILO_DEFAULT_COUNTRY;
        $sql = serchilo_replace_sql_arguments(
          $mysqli, 
          $sql,
          array(
            'telegram_user_id'  => $telegram_user_id,
            'uid'               => NULL,
            'namespaces_path'   => $namespaces_path,
          )
        );

        $result = $mysqli->query($sql);

        $text = 
          "Welcome to the @FindFindBot. You can use now shortcuts from [FindFind.it](https://www.findfind.it) right here in Telegram. [Learn more about FindFind.it](https://www.findfind.it/help/start). " . PHP_EOL . PHP_EOL . 
          "I have just set up the default namespaces for you: $namespaces_path. You can change them with /n or /u. [Learn more about namespaces](https://www.findfind.it/help/namespaces)."; 

        $message = $this->getMessage();
        $chat_id = $message->getChat()->getId();

        $data = [
          'chat_id' => $chat_id,
          'text'    => $text,
          'parse_mode' => 'Markdown',
          'disable_web_page_preview' => TRUE,
        ];

        return Request::sendMessage($data);
    }
}
