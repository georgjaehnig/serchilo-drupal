# serchilo-drupal

Drupal profile running Serchilo

## Install

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

# First Enable Serchilo Features
drush pm-enable serchilo_features -y
# ... then the module itself.
# (Doesn't work via module depency because, weirdly, 
# dependencies get enable _after_ the module)
drush pm-enable serchilo -y

# Strongarm somehow looses this, so we need to do it manually
drush vset theme_default bootstrap_serchilo
drush vset pathauto_node_pattern [node:title]

```

To `drupal/.htaccess`, add:
```
# call with namespaces
RewriteCond %{REQUEST_URI} ^\/n\/.*
# must have 'query' parameter
RewriteCond %{QUERY_STRING} (^|&)query=
RewriteRule ^(.*)$ profiles/profilo/modules/serchilo/process/?page_type=console&call_type=n [L,QSA]

# call with user name
RewriteCond %{REQUEST_URI} ^\/u\/.*
# must have 'query' parameter
RewriteCond %{QUERY_STRING} (^|&)query=
RewriteRule ^(.*)$ profiles/profilo/modules/serchilo/process/?page_type=console&call_type=u [L,QSA]

# must start with 'u' or 'n'
RewriteCond %{REQUEST_URI} ^\/ajax\/(u|n)\/.*
# must have 'query' parameter
RewriteCond %{QUERY_STRING} (^|&)term=
RewriteRule ^(.*)$ profiles/profilo/modules/serchilo/process/?page_type=ajax [L,QSA]
```
