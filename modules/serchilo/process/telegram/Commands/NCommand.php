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


        $message = $this->getMessage();
        $chat_id = $message->getChat()->getId();

        $message_id = $message->getMessageId();
        $command = trim($message->getText(true));

        //Only get enabled Admin and User commands
        $commands = array_filter($this->telegram->getCommandsList(), function ($command) {
            return (!$command->isSystemCommand() && $command->isEnabled());
        });

        //If no command parameter is passed, show the list
        if ($command === '') {
            $text = $this->telegram->getBotName() . ' v. ' . $this->telegram->getVersion() . "\n\n";
            $text .= 'Commands List:' . "\n";
            foreach ($commands as $command) {
                $text .= '/' . $command->getName() . ' - ' . $command->getDescription() . "\n";
            }

            $text .= "\n" . 'For exact command help type: /help <command>';
        } else {
            $command = str_replace('/', '', $command);
            if (isset($commands[$command])) {
                $command = $commands[$command];
                $text = 'Command: ' . $command->getName() . ' v' . $command->getVersion() . "\n";
                $text .= 'Description: ' . $command->getDescription() . "\n";
                $text .= 'Usage: ' . $command->getUsage();
            } else {
                $text = 'No help available: Command /' . $command . ' not found';
            }
        }

        $data = [
            'chat_id'             => $chat_id,
            'reply_to_message_id' => $message_id,
            'text'                => $text,
        ];

        return Request::sendMessage($data);
    }
}
