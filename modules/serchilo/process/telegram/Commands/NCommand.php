<?php

namespace Longman\TelegramBot\Commands\UserCommands;

use Longman\TelegramBot\Commands\UserCommand;
use Longman\TelegramBot\Request;

class NCommand extends UserCommand
{
    /**#@+
     * {@inheritdoc}
     */
    protected $name = 'n';
    protected $description = 'Set the namespaces that shall be used.';
    protected $usage = '/n <namespaces separated with dots>';
    protected $version = '1.0.0';
    protected $need_mysql = false;
    /**#@-*/

    /**
     * {@inheritdoc}
     */
    public function execute()
    {
        $message = $this->getMessage();
        $namespaces_path = $message->getText(TRUE);

        if (!empty($namespaces_path)) {
          $text = 'Using now the namespaces: ' . $namespaces_path;
          $telegram_user_id = $this->getUpdate()->getMessage()->getFrom()->getId();
          serchilo_telegram_remove_settings($telegram_user_id);
          serchilo_telegram_set_namespaces($telegram_user_id, $namespaces_path);
        } else {
          $text = $this->description . PHP_EOL . 'Usage: ' . $this->usage; 
        }

        return Request::sendMessage([
          'chat_id' => $message->getChat()->getId(),
          'text'    => $text
        ]);
    }
}
