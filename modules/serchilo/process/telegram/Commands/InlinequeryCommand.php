<?php

namespace Longman\TelegramBot\Commands\SystemCommands;

use Longman\TelegramBot\Commands\SystemCommand;
use Longman\TelegramBot\Entities\InlineQueryResultArticle;
use Longman\TelegramBot\Entities\InputTextMessageContent;
use Longman\TelegramBot\Request;

/**
 * Inline query command
 */
class InlinequeryCommand extends SystemCommand
{
    /**#@+
     * {@inheritdoc}
     */
    protected $name = 'inlinequery';
    protected $description = 'Reply to inline query';
    protected $version = '1.0.2';
    /**#@-*/

    /**
     * {@inheritdoc}
     */
    public function execute()
    {
        $env = $this->getConfig('env');

        $update = $this->getUpdate();
        $inline_query = $update->getInlineQuery();
        $telegram_user_id = $inline_query->getFrom()->getId();
        serchilo_telegram_get_settings($env, $telegram_user_id);

        $query = $inline_query->getQuery();
        $data = ['inline_query_id' => $inline_query->getId()];

        if (empty($query)) {
            return Request::answerInlineQuery($data);
        }

        $env['query'] = $query;
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

        // TODO: Replace this with serchilo_search_shortcuts().
        $output = serchilo_get_output($env);

        if (!$output['status']['found']) {
            return Request::answerInlineQuery($data);
        }

        $results = [];
        $articles = [
          [
            'id' => (string) 1, // shortcut id 
            'title' => $output['#shortcut']['title'], //'https://core.telegram.org/bots/api#answerinlinequery',  // shortcut title
            'description' => trim($output['#shortcut']['keyword'] . ' ' .  $output['#shortcut']['argument_names']),
            // TODO: Show namespace.
            'input_message_content' => new InputTextMessageContent([
              'message_text' => $env['query'] . ' → ' . $output['url']['final'],
            ])
          ],
        ];

        foreach ($articles as $article) {
            $results[] = new InlineQueryResultArticle($article);
        }

        $data['results'] = '[' . implode(',', $results) . ']';

        return Request::answerInlineQuery($data);
    }
}
