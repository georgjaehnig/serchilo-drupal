# serchilo-drupal

Drupal profile running Serchilo (a new version, currently being developed).

## Install

### Requirements

- PHP >= 5.3.0 (probably)
- MySQL >= 5.0 (probably)
- [drush](http://drush.ws/)

### Preparations
```
# create a new directory, for instance serchilo/
# and change into it

mkdir serchilo
cd serchilo

# Get the Serchilo Drupal profile 
git clone git@github.com:georgjaehnig/serchilo-drupal.git profilo

# Download drupal with drush
drush dl drupal 

# Rename downloaded dir
mv drupal-* drupal

# Move Serchilo profile to profiles/
mv profilo drupal/profiles/
```
### Run Drupal installer

- Set up a local virtual host pointing to `drupal/`, for instance called `http://l.serchilo/`.
- Run drupal installer in your browser, simply by calling the main page `http://l.serchilo/`.
- In the installer, choose `Serchilo Profilo` as installation profile.
- During install, you need to create a writable `files/` dir and `settings.php` file:
```
mkdir drupal/sites/default/files
chmod 777 drupal/sites/default/files
cp drupal/sites/default/default.settings.php drupal/sites/default/settings.php
chmod 777 drupal/sites/default/settings.php
```
- Additionally, you will be asked to set up a database. Create one and enter its credentials in the installer.

### After installing Drupal
```
# Change into drupal/ directory
cd drupal

# Enable the theme
drush dl bootstrap
drush pm-enable bootstrap_serchilo -y

# First Enable Serchilo features module
drush pm-enable serchilo_features -y

# ... then the module itself.
drush pm-enable serchilo -y

# Set some variables
# (Strongarm somehow looses these ones, 
# so we need to do set them manually)
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

# call with namespaces
RewriteCond %{REQUEST_URI} ^\/n\/.*
# must have 'query' parameter
RewriteCond %{QUERY_STRING} (^|&)term=
RewriteRule ^(.*)$ profiles/profilo/modules/serchilo/process/?page_type=ajax&call_type=n [L,QSA]

# call with user name
RewriteCond %{REQUEST_URI} ^\/u\/.*
# must have 'query' parameter
RewriteCond %{QUERY_STRING} (^|&)term=
RewriteRule ^(.*)$ profiles/profilo/modules/serchilo/process/?page_type=ajax&call_type=u [L,QSA]
```

That's it. You should now be able to see Serchilo in your browser at `http://l.serchilo/`.
