<?PHP

require_once('../serchilo.constants.inc');
require_once('../serchilo.overall.inc');
require_once('index.php');


for ($i=0; $i<10000; $i++) {
  $res = serchilo_get_values_from_table('taxonomy_vocabulary', 'machine_name', 'namespaces', 'vid');
  #print_r($res);
}
print "done";
