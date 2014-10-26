<div class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php if (!$label_hidden): ?>
    <div class="field-label"<?php print $title_attributes; ?>><?php print $label ?>:&nbsp;</div>
  <?php endif; ?>
  <div class="field-items"<?php print $content_attributes; ?>>

    <dl class="dl-horizontal">

    <?php foreach ($items as $delta => $item): ?>
      <dt>
        <?php

// Horrible wrapper code due to Field collection's tpl cascade bug:
// https://www.drupal.org/node/1137024
if (isset($item['entity']['field_collection_item'])) {
  print render(current($item['entity']['field_collection_item'])['field_example_arguments'][0]);
} elseif (is_string($item)) {
  print $item;
}

        ?>
      </dt>
      <dd>
        <?php
if (isset($item['entity']['field_collection_item'])) {
  print render(current($item['entity']['field_collection_item'])['field_example_description'][0]);
} elseif (is_string($item)) {
  print $item;
}
        ?>
      </dd>
    <?php endforeach ?>

    </dl>

  </div>
</div>
