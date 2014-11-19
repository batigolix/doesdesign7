<?php

/**
 * @file
 * Migrate definitions for the Veldeke dictionary.
 */


/**
 * Defines a dynamic migration that is reused for each source CSV file.
 */
class VeldekeDictionaryMigration extends DynamicMigration {

  /**
   * Constructs the migration.
   */
  public function __construct() {
    parent::__construct();
    $this->description = t('Import dictionary from CSV file.');

    // Creates a map object for tracking the relationships between source rows.
    $this->map = new MigrateSQLMap($this->machineName, array(
        'id' => array(
          'type' => 'int',
          'length' => 24,
          'not null' => TRUE,
          'description' => 'ID',
        ),
      ), MigrateDestinationNode::getKeySchema()
    );

    // Creates a source object that contains the data.
    if ($wrapper = file_stream_wrapper_get_instance_by_uri('public://')) {
      $realpath = $wrapper->realpath();
    }

    $this->path = $realpath . '/veldeke-dictionary.csv';
    $this->source = new MigrateSourceCSV($this->path, $this->csvcolumns(), array());

    // Creates a destination object that receives the data.
    $this->destination = new MigrateDestinationNode('dictionary_entry');

    $this->addFieldMapping('title', 'head_word')->description('Title');
    $this->addFieldMapping('field_head_word', 'head_word');
    $this->addFieldMapping('field_translation', 'translation');
    $this->addFieldMapping('field_conjugation', 'conjugation');
    $this->addFieldMapping('field_remark', 'remark');
    $this->addFieldMapping('field_1st_char_head_word', 'first_char_head_word');
    $this->addFieldMapping('field_1st_char_translation', 'first_char_translation');

    // Defines unmapped destination fields.
    $this->addFieldMapping('status')->issueGroup(t('DNM'));
    $this->addFieldMapping('uid')->issueGroup(t('DNM'));
    $this->addFieldMapping('changed')->issueGroup(t('DNM'));
    $this->addFieldMapping('created')->issueGroup(t('DNM'));
    $this->addFieldMapping('promote')->issueGroup(t('DNM'));
    $this->addFieldMapping('sticky')->issueGroup(t('DNM'));
    $this->addFieldMapping('revision')->issueGroup(t('DNM'));
    $this->addFieldMapping('log')->issueGroup(t('DNM'));
    $this->addFieldMapping('language')->issueGroup(t('DNM'));
    $this->addFieldMapping('tnid')->issueGroup(t('DNM'));
    $this->addFieldMapping('translate')->issueGroup(t('DNM'));
    $this->addFieldMapping('revision_id')->issueGroup(t('DNM'));
    $this->addFieldMapping('revision_uid')->issueGroup(t('DNM'));
    $this->addFieldMapping('is_new')->issueGroup(t('DNM'));
    $this->addFieldMapping('path')->issueGroup(t('DNM'));
    $this->addFieldMapping('comment')->issueGroup(t('DNM'));

    // Defines unmapped source fields.
    $this->addFieldMapping(NULL, 'date')->issueGroup(t('DNM'));
    $this->addFieldMapping(NULL, 'id')->issueGroup(t('DNM'));
    $this->addFieldMapping(NULL, 'first_char')->issueGroup(t('DNM'));

  }

  /**
   * Assigns csv column data to key.
   */
  function csvcolumns() {
    $columns[0] = array('id', 'ID');
    $columns[1] = array('date', 'Date');
    $columns[3] = array('head_word', 'Head word');
    $columns[4] = array('translation', 'Translation');
    $columns[5] = array('conjugation', 'Conjugation');
    $columns[6] = array('remark', 'Remark');
    $columns[2] = array('first_char', '1st char');
    return $columns;
  }

  /**
   * Prepares rows before import.
   */
  function prepareRow($row) {
    $row->first_char_head_word = strtolower(_remove_accents($row->head_word));
    $row->first_char_head_word = $row->first_char_head_word[0];
    $row->first_char_translation = strtolower(_remove_accents($row->translation));
    $row->first_char_translation = $row->first_char_translation[0];
  }

}
