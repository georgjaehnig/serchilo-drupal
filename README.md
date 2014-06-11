
# Install

```
# Install drush

# create a new directory, for instance serchilo/
# and change into it

mkdir serchilo
cd serchilo

# Get the Serchilo Drupal profile 
git clone serchilo-drupal-profile profilo

# Download drupal with drush
drush dl drupal 

# Rename downloaded dir
mv drupal-* drupal

# Move Serchilo profile to profiles/
mv profilo drupal/profiles/

# Set up a local virtual host pointing to drupal/
# for instance called http://l.serchilo/

# run drupal installer in your browser,
# simply by calling the main page http://l.serchilo/

# In the installer, 
# - Choose Serchilo Profilo!!

# During install, you need to create writable files/ dir and settings.php file:
mkdir drupal/sites/default/files
chmod 777 drupal/sites/default/files

cp drupal/sites/default/default.settings.php drupal/sites/default/settings.php
chmod 777 drupal/sites/default/settings.php

# Additionally, you will be asked to set up a database.
# Finish Drupal install in your web browser.

# Change into drupal/ directory
cd drupal

# Enable Serchilo theme
drush dl bootstrap
drush pm-enable bootstrap_serchilo -y

# Enable Serchilo module
# You will be prompted to agree to download further modules, say yes.
drush pm-enable serchilo -y

# Strongarm somehow looses this, so we need to do it manually
drush vset theme_default bootstrap_serchilo
drush vset pathauto_node_pattern [node:title]

```
