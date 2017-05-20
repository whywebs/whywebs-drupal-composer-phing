<?php

/**
 * @file
 * Provides View page for selected date to change only slot capacity.
 */

/**
 * Implements hook_form().
 */
function appointment_calendar_view_date_form($form, $form_state) {
  // Date edit page.
  if (!empty($_GET['date'])) {
    $form['redirect'] = array(
      '#markup' => '<a href="/admin/config/appointment-calendar/settings">Goto Appointment Calendar Setting Page</a><br>',
    );
    $form['listredirect'] = array(
      '#markup' => '<a href="/admin/config/appointment-calendar/settings/list-date">Goto Appointment Calendar Listing Page</a>',
    );
    $form['appointment_slot_date'] = array(
      '#type' => 'textfield',
      '#title' => 'Date',
      '#default_value' => date('Y-m-d', $_GET['date']),
      '#disabled' => TRUE,
    );
    // Fetching Slot previous capacity filled.
    $capacity = appointment_calendar_slot_capacity($_GET['date']);
    $header = ['Slot Time', 'No. Of Slots alloted', 'Booked Slots', 'Status'];
    $i = 1;
    // Show slots and capacity.
    foreach (json_decode($capacity) as $key => $value) {
      // Check if any appointment booked.
      $date = db_like(date('Y-m-d', $_GET['date'])) . 'T' . $key;
      $explode_date = explode(':', ($date));
      $date_query = db_select('field_data_appointment_date', 'ap');
      $date_query->fields('ap', array('appointment_date_value '));
      $date_query->condition('ap.appointment_date_value', $explode_date[0] . ':00:00', '=');
      $date_queryresult = $date_query->execute()->fetchAll(PDO::FETCH_ASSOC);
      $slot_check = count($date_queryresult);
      if ($slot_check >= $value) {
        $row[$key]['slot'] = $key;
        $row[$key]['no_slots'] = $value;
        $row[$key]['booked_slots'] = $slot_check;
        $row[$key]['status'] = 'Booked';
      }
      else {
        $row[$key]['slot'] = $key;
        $row[$key]['no_slots'] = $value;
        $row[$key]['booked_slots'] = $slot_check;
        $row[$key]['status'] = 'Free';
      }
    }
    $output = theme('table', array('header' => $header, 'rows' => $row));
    $form['ouptut'] = array(
      '#markup' => $output,
    );
    return $form;
  }
}
