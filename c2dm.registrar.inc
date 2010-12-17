<?php

function c2dm_register() {
	$device_id = $_POST['device_id'];
	$registration_id = $_POST['registration_id'];
	$gem_name = $_POST['gem_name'];
	$gem_version = $_POST['gem_version'];
	$gem_patch = $_POST['gem_patch'];
	$device = $_POST['device'];

	// verify that none of these are null
	if(empty($device_id) ||
	   empty($registration_id) ||
	   empty($gem_name) ||
	   empty($gem_version) ||
	   empty($device)) {
		return 'Invalid data supplied for registration';		
	}

	// see if this device already exists
	$result = db_query('SELECT `device_id`' .
				' FROM `c2dm_devices`' .
				' WHERE `device_id` = \'%s\';',
			$device_id);

	if(db_fetch_array($result) == false) {
		// nothing there, time to insert!
		db_query('INSERT INTO `c2dm_devices` (' .
				'`device_id`, `registration_id`, `gem_name`, `gem_version`,' .
				'`gem_patch`, `device`) VALUES (' .
				'\'%s\', \'%s\', \'%s\', \'%s\',' .
				'\'%s\', \'%s\');',
			$device_id, $registration_id, $gem_name, $gem_version,
			$gem_patch, $device);
	} else {
		// something there, time to update!
		db_query('UPDATE `c2dm_devices` SET ' .
				'`registration_id` = \'%s\',' .
				'`gem_name` = \'%s\',' .
				'`gem_version` = \'%s\',' .
				'`gem_patch` = \'%s\',' .
				'`device` = \'%s\' ' .
				'WHERE `device_id` = \'%s\';',
			$registration_id, $gem_name, $gem_version, $gem_patch, $device,
			$device_id);
	}

	return 'Registered';
}

function c2dm_unregister() {
	$device_id = $_POST['device_id'];

	if(empty($device_id)) {
		return 'Invalid data supplied for unregistration.';
	}

	// attempt deletion
	db_query('DELETE FROM `c2dm_devices` WHERE `device_id` = \'%s\';', $device_id);

	return 'Unregistered';
}

function __c2dm_validate() {
}
