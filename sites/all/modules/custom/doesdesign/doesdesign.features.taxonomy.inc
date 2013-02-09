<?php
/**
 * @file
 * doesdesign.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function doesdesign_taxonomy_default_vocabularies() {
  return array(
    'vocabulary_6' => array(
      'name' => 'Materiaal',
      'machine_name' => 'vocabulary_6',
      'description' => 'Bekijk sieraden aan de hand van de gebruikte materialen.',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
    ),
    'vocabulary_7' => array(
      'name' => 'Sieraden en objecten',
      'machine_name' => 'vocabulary_7',
      'description' => 'Sieraden en objecten met als specialiteit Mokume-gane',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
    ),
    'vocabulary_8' => array(
      'name' => 'Jaar',
      'machine_name' => 'vocabulary_8',
      'description' => 'Jaar waarin object gemaakt werd',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
    ),
  );
}
