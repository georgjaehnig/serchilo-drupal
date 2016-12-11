<?php

namespace Longman\TelegramBot\Commands\UserCommands;

use Longman\TelegramBot\Commands\UserCommand;
use Longman\TelegramBot\Request;

class UCommand extends UserCommand
{
    /**#@+
     * {@inheritdoc}
     */
    protected $name = 'u';
    protected $description = 'Set the user whose namespaces shall be used.';
    protected $usage = '/u <username>';
    protected $version = '1.0.0';
    protected $need_mysql = false;
    /**#@-*/

    /**
     * {@inheritdoc}
     */
    public function execute()
    {
        $message = $this->getMessage();
        $user_name = $message->getText(TRUE);

        if (empty($user_name)) {
          $text = $this->description . PHP_EOL . 'Usage: ' . $this->usage; 
        }
        if (!empty($user_name)) {
          $uid = serchilo_get_values_from_table('users', 'name', $user_name, 'uid')[0];
          if (empty($uid)) {
            $text = 'Could not find user with the name: ' . $user_name;
          }
        } 
        if (!empty($uid)) {
          $telegram_user_id = $this->getUpdate()->getMessage()->getFrom()->getId();
          serchilo_telegram_remove_settings($telegram_user_id);
          serchilo_telegram_set_settings($telegram_user_id, NULL, $uid);
          $text = 'Using now the namespaces of user: ' . $user_name;
        }

        return Request::sendMessage([
          'chat_id' => $message->getChat()->getId(),
          'text'    => $text
        ]);
    }
}
