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
        $query = $inline_query->getQuery();
        $data = ['inline_query_id' => $inline_query->getId()];

        if (empty($query)) {
            return Request::answerInlineQuery($data);
        }

        $results = [];
        $articles = [
          [
            'id' => (string) 1, // shortcut id 
            'title' => 'https://core.telegram.org/bots/api#answerinlinequery',  // shortcut title
            'description' => 'you enter: ' . $query,  // usage
            'input_message_content' => new InputTextMessageContent(['message_text' => ' i' . $query])
          ],
        ];

        foreach ($articles as $article) {
            $results[] = new InlineQueryResultArticle($article);
        }

        $data['results'] = '[' . implode(',', $results) . ']';

        return Request::answerInlineQuery($data);
    }
}
