<?php

namespace Serchilo\Telegram\Commands;

use Telegram\Bot\Actions;
use Telegram\Bot\Commands\Command;

class SetUserCommand extends Command
{
    /**
     * @var string Command Name
     */
    protected $name = "u";

    /**
     * @var string Command Description
     */
    protected $description = "Set a FindFind.it user name to use their namespace settings.";

    /**
     * @inheritdoc
     */
    public function handle($arguments)
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

        $sql = serchilo_replace_sql_arguments(
          $mysqli, 
          $sql,
          array(
            'telegram_user_id'  => $telegram_user_id,
            'uid'               => 3,
            'namespaces_path'   => $namespaces_path,
          )
        );

        $result = $mysqli->query($sql);

        $text = 
          "Enter a user name to use that user's namespaces.";

        $this->replyWithMessage([
          'text' => $text,
          'parse_mode' => 'Markdown',
          'disable_web_page_preview' => TRUE,
        ]);
    }
}
