# serchilo-drupal

Drupal profile running Serchilo (a new version, currently being developed).
- Demo: http://serchilo.org/
- current official version (not this code here) http://www.serchilo.net/
- mailing list: https://groups.google.com/d/forum/serchilo


## Install

### Requirements

- PHP >= 5.4 (probably)
  - with GeoIP module, install with: `sudo apt-get install php5-geoip`
  - with GD extension, install with: `sudo apt-get install php5-gd`
  - with MySQL Native Driver, install with: `sudo apt-get install php5-mysqlnd`
- MySQL >= 5.0 (probably)
- [drush](http://drush.ws/)
- Apache server with mod_rewrite enabled
  - if not, enable with `sudo a2enmod rewrite`

### Preparations
```
# create a new directory, for instance serchilo/
# and change into it

mkdir serchilo
cd serchilo

# Download drupal with drush
drush dl --drupal-project-rename

# Change to profiles/
cd drupal/profiles/

# Get the Serchilo Drupal profile with submodules
git clone https://github.com/georgjaehnig/serchilo-drupal.git serchilo_profile
cd serchilo_profile
git submodule init
git submodule update
cd ../..

```
Your directory structure should now look like this:
```
serchilo/
  drupal/
    profiles/
      serchilo_profile/
      ...
    ...
```
### Run Drupal installer

- Set up a local virtual host pointing to `drupal/`, for instance called `http://l.serchilo/`.
- Run drupal installer in your browser, simply by calling the main page `http://l.serchilo/`.
- In the installer, choose `Serchilo profile` as installation profile.
- During install, you need to create a writable `files/` dir and `settings.php` file:
```
mkdir sites/default/files
chmod 777 sites/default/files
cp sites/default/default.settings.php sites/default/settings.php
chmod 777 sites/default/settings.php
```
- Additionally, you will be asked to set up a database. Create one and enter its credentials in the installer.
  - (For currently unknown reasons, you might be asked twice for entering the database credentials. Additionally, after clicking "Save and continue", a white page may appear. Clicking back and forward on the browser resolves the issue, though. Both is an ugly issue, if you know what might help please tell.)

### After installing Drupal
```

# Enable the theme
drush dl bootstrap
drush pm-enable bootstrap_serchilo -y

# Download Clone module manually because of its Namespace inconsistency
drush dl node_clone -y

# First Enable Serchilo features module
drush pm-enable serchilo_features -y

# ... then the module itself.
drush pm-enable serchilo -y
drush features-revert-all -y
```

To `drupal/.htaccess`, add:
```
# Console call
# must have 'query' parameter
RewriteCond %{QUERY_STRING} (^|&)query=
RewriteCond %{QUERY_STRING} !(^|&)status=not_found
RewriteCond %{REQUEST_URI} ^\/(n|u)\/.*
RewriteRule ^.*$ profiles/serchilo_profile/modules/serchilo/process/?page_type=console&call_type=%1 [L,QSA]

# Non-console call
RewriteCond %{QUERY_STRING} (^|&)(query|term|keyword)=
RewriteCond %{REQUEST_URI} ^\/(ajax|opensearch-suggestions|api|url)\/(n|u)\/.*
RewriteRule ^.*$ profiles/serchilo_profile/modules/serchilo/process/?page_type=%1&call_type=%2 [L,QSA]

# Send out Safari extension
AddType application/octet-stream .safariextz

# Apache Log settings
# Do not log command queries.
RewriteCond %{QUERY_STRING} query=
RewriteRule  (.*)   $1 [E=nolog:yes]
# Do not log autocomplete queries.
RewriteCond %{REQUEST_URI} ^/ajax/
RewriteCond %{QUERY_STRING} term=
RewriteRule  (.*)   $1 [E=nolog:yes]
```

That's it. You should now be able to see Serchilo in your browser at `http://l.serchilo/`.

## Update

If you already have Serchilo installed and want to update the code and Serchilo's settings:
```
git pull
drush cache-clear all
drush pm-disable serchilo
drush pm-enable serchilo
```
