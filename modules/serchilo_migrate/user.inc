<?PHP

class SerchiloUserMigration extends DrupalUser7Migration {

  public function __construct($arguments) {
     parent::__construct($arguments);

     // Simply copy the default keyword string.
     $this->addFieldMapping('field_default_keyword',    'field_default_keyword');

     // Map the old tid to the new one.
     $this
       ->addFieldMapping('field_language_namespace', 'field_language_namespace')
       ->arguments(array('source_type' => 'tid'))
       ->sourceMigration(array('SerchiloNamespaceTerm'))
       ;
     $this
       ->addFieldMapping('field_country_namespace',  'field_country_namespace')
       ->arguments(array('source_type' => 'tid'))
       ->sourceMigration(array('SerchiloNamespaceTerm'))
       ;
     $this
       ->addFieldMapping('field_custom_namespaces',  'field_custom_namespaces')
       ->arguments(array('source_type' => 'tid'))
       ->sourceMigration(array('SerchiloNamespaceTerm'))
       ;
  }
}
