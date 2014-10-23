<div class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php if (!$label_hidden): ?>
    <div class="field-label"<?php print $title_attributes; ?>><?php print $label ?>:&nbsp;</div>
  <?php endif; ?>
  <div class="field-items"<?php print $content_attributes; ?>>

    <dl class="dl-horizontal">

    <?php foreach ($items as $delta => $item): ?>
      <dt>
        <?php
          print render(current($item['entity']['field_collection_item'])['field_example_arguments'][0]);
        ?>
      </dt>
      <dd>
        <?php
          print render(current($item['entity']['field_collection_item'])['field_example_description'][0]);
        ?>
      </dd>
    <?php endforeach ?>

    </dl>

  </div>
</div>
