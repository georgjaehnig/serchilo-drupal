# serchilo-drupal

Drupal profile running Serchilo (a new version, currently being developed).
- Demo: http://serchilo.org/
- current official version (not this code here) http://www.serchilo.net/
- mailing list: https://groups.google.com/d/forum/serchilo


## Install

### Requirements

- PHP >= 5.4 (probably)
  - with GeoIP module, install with: `sudo apt-get install php5-geoip`
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
git clone https://github.com/georgjaehnig/serchilo-drupal.git profilo
cd profilo
git submodule init
git submodule update
cd ../..

```
Your directory structure should now look like this:
```
serchilo/
  drupal/
    profiles/
      profilo/
      ...
    ...
```
### Run Drupal installer

- Set up a local virtual host pointing to `drupal/`, for instance called `http://l.serchilo/`.
- Run drupal installer in your browser, simply by calling the main page `http://l.serchilo/`.
- In the installer, choose `Serchilo Profilo` as installation profile.
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

# First Enable Serchilo features module
drush pm-enable serchilo_features -y

# ... then the module itself.
drush pm-enable serchilo -y
```

To `drupal/.htaccess`, add:
```
# call with namespaces
RewriteCond %{REQUEST_URI} ^\/n\/.*
# must have 'query' parameter
RewriteCond %{QUERY_STRING} (^|&)query=
RewriteCond %{QUERY_STRING} !(^|&)status=not_found
RewriteRule ^(.*)$ profiles/profilo/modules/serchilo/process/?page_type=console&call_type=n [L,QSA]

# call with user name
RewriteCond %{REQUEST_URI} ^\/u\/.*
# must have 'query' parameter
RewriteCond %{QUERY_STRING} (^|&)query=
RewriteCond %{QUERY_STRING} !(^|&)status=not_found
RewriteRule ^(.*)$ profiles/profilo/modules/serchilo/process/?page_type=console&call_type=u [L,QSA]

# call with namespaces
RewriteCond %{REQUEST_URI} ^\/ajax\/n\/.*
# must have 'query' parameter
RewriteCond %{QUERY_STRING} (^|&)term=
RewriteRule ^(.*)$ profiles/profilo/modules/serchilo/process/?page_type=ajax&call_type=n [L,QSA]

# call with user name
RewriteCond %{REQUEST_URI} ^\/ajax\/u\/.*
# must have 'query' parameter
RewriteCond %{QUERY_STRING} (^|&)term=
RewriteRule ^(.*)$ profiles/profilo/modules/serchilo/process/?page_type=ajax&call_type=u [L,QSA]

# call with namespaces
RewriteCond %{REQUEST_URI} ^\/opensearch-suggestions\/n\/.*
# must have 'query' parameter
RewriteCond %{QUERY_STRING} (^|&)query=
RewriteRule ^(.*)$ profiles/profilo/modules/serchilo/process/?page_type=opensearch-suggestions&call_type=n [L,QSA]

# call with user name
RewriteCond %{REQUEST_URI} ^\/opensearch-suggestions\/u\/.*
# must have 'query' parameter
RewriteCond %{QUERY_STRING} (^|&)query=
RewriteRule ^(.*)$ profiles/profilo/modules/serchilo/process/?page_type=opensearch-suggestions&call_type=u [L,QSA]
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
