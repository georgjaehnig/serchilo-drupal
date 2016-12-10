<?php
/**
 * This file is part of the TelegramBot package.
 *
 * (c) Avtandil Kikabidze aka LONGMAN <akalongman@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace Longman\TelegramBot\Commands\SystemCommands;

use Longman\TelegramBot\Conversation;
use Longman\TelegramBot\Request;
use Longman\TelegramBot\Commands\SystemCommand;

/**
 * Generic message command
 */
class GenericmessageCommand extends SystemCommand
{
    /**#@+
     * {@inheritdoc}
     */
    protected $name = 'Genericmessage';
    protected $description = 'Handle generic message';
    protected $version = '1.0.2';
    protected $need_mysql = false;
    /**#@-*/

    /**
     * Execution if MySQL is required but not available
     *
     * @return boolean
     */
    public function executeNoDb()
    {
        //Do nothing
        return Request::emptyResponse();
    }

    /**
     * Execute command
     *
     * @return boolean
     */
    public function execute()
    {
        $env = $this->getConfig('env');

        $message = $this->getMessage();

        $env['query'] = $message->getText();

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

        //error_log(json_encode($env));

        $output = serchilo_get_output($env);

        if ($output['status']['found']) {
          $url = $output['url']['final'];
          serchilo_log_shortcut_call($output['#shortcut'], $env, $output['status']['default_keyword_used']);
        } else {
          $text = 'Error: No shortcut found.';
        }

        return Request::sendMessage([
          'chat_id' => $message->getChat()->getId(),
          'text'    => (!empty($url) ? $url : $text), // json_encode($env), // $message->getText(),
        ]);
    }
}
