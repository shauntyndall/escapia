<?php

class EscapiaAPIBookingRates {
  public $UnitStay;
  public $Warnings;
  public $Errors;
  public $Success;

  public function __construct($_unitStay = NULL,$_warnings = NULL,$_errors = NULL,$_success = NULL) {
    $this->UnitStay = $_unitStay;
    $this->Warnings = $_warnings;
    $this->Errors = $_errors;
    $this->Success = $_success;
  }

  public function getBasePrice() {
    return array(
      'beforeTax' => (float)$this->UnitStay->UnitRates->UnitRate->Rates->Rate->Base->AmountBeforeTax,
      'taxAmount' => (float)$this->UnitStay->UnitRates->UnitRate->Rates->Rate->Base->Taxes->Amount,
    );
  }

  public function getTotalPrice() {
    return array(
      'beforeTax' => (float)$this->UnitStay->Total->AmountBeforeTax,
      'taxAmount' => (float)$this->UnitStay->Total->Taxes->Amount,
    );
  }

  public function getRentalBookingAgreement() {
    $output = '';
    if(isset($this->UnitStay->RentalAgreement) ) {
      $output =  $this->UnitStay->RentalAgreement->Description->Text;
    }
    return $output;
  }

  public function getRentalCancellationPolicy() {
    $output = '';
    if($this->UnitStay->CancelPenalties->CancelPolicyIndicator && $policy = $this->UnitStay->CancelPenalties->CancelPenalty) {
      $output = ($policy->PenaltyDescription->Name == 'Cancellation Policy') ? $policy->PenaltyDescription->Text->_ : '';
    }
    return $output;
  }

  // UnitStay->UnitRates->UnitRate->Rates->Rate->Fees
  public function getRequiredChargesDetails() {
    $output = false;
    if($charges = $this->UnitStay->UnitRates->UnitRate->Rates->Rate->Fees) {
      if (isset($charges->Fee) && is_object($charges->Fee)) {
        $output[] = $this->_getFeesDetails($charges->Fee);
      }
      elseif (isset($charges->Fee) && is_array($charges->Fee)) {
        foreach($charges->Fee as $i => $charge) {
          $output[] = $this->_getFeesDetails($charge);
        }
      }
    }
    return $output;
  }

  // UnitStay->UnitRates->UnitRate->Rates->Rate->AdditionalCharges
  public function getOptionalChargesDetails() {
    $output = false;
    if($charges = $this->UnitStay->UnitRates->UnitRate->Rates->Rate->AdditionalCharges) {
      if (isset($charges->AdditionalCharge) && is_object($charges->AdditionalCharge)) {
        $output[] = $this->_getChargesDetails($charges->AdditionalCharge);
      }
      elseif (isset($charges->AdditionalCharge) && is_array($charges->AdditionalCharge)) {
        foreach($charges->AdditionalCharge as $i => $charge) {
          $output[] = $this->_getChargesDetails($charge);
        }
      }
    }
    return $output;
  }

  public function get_SUMM_OptionalCharges($type = 'beforeTax') {
    $charges = $this->getOptionalChargesDetails();
    if($charges && in_array($type, array('beforeTax', 'taxAmount'))) {
      $total = (float)0;
      foreach($charges as $charge) {
        if(!$charge['included'])
          $total = bcadd($total, $charge[$type], 2);
      }
      return $total;
    }
    else
      return false;
  }

  public function get_SUMM_Fees($type = 'beforeTax') {
    $charges = $this->getRequiredChargesDetails();
    if($charges  && in_array($type, array('beforeTax', 'taxAmount'))) {
      $total = (float)0;
      foreach($charges as $charge) {
        if($charge['required']) {
          if($type == 'beforeTax' && $charge['inclusiveness'] == 'Exclusive') {
            $total = bcadd($total, $charge[$type], 2);
          }
          elseif($type == 'taxAmount') {
            $total = bcadd($total, $charge[$type], 2);
          }
        }
      }
      return $total;
    }
    else
      return false;
  }

  private function _getChargesDetails($charge){
    $output = array(
      'included' => ($charge->Quantity == 0) ? false : true,
      'beforeTax' => (float)$charge->Amount->AmountBeforeTax,
      'taxAmount' => (float)$charge->Amount->Taxes->Amount,
    );
    foreach($charge->Description as $i => $val) {
      if($val->Name == 'Charge Description') {
        $output['label'] = $val->Text->_;
        break;
      }
    }
    return $output;
  }

  private function _getFeesDetails($charge){
    $output = array(
      'tax_included' => $charge->TaxInclusive,
      'inclusiveness' => $charge->Type,
      'required' => $charge->MandatoryIndicator,
      'beforeTax' => (float)$charge->Amount,
      'taxAmount' => (float)$charge->Taxes->Amount,
      'currency' => $charge->CurrencyCode,
      'subtotal' => (float)$charge->Amount,
    );
    if ($charge->Type == 'Inclusive') {
      $output['subtotal'] = bcadd($output['subtotal'], $output['taxAmount'], 2);
    }

    foreach($charge->Description as $i => $val) {
//      foreach($charge['description'] as $i => $val) {
      if($val->Name == 'Charge Description') {
        $output['label'] = $val->Text->_;
        break;
      }
    }
    return $output;
  }


  public function getBasePriceTaxes() {
    $output = array();

    $taxes = $this->UnitStay->UnitRates->UnitRate->Rates->Rate->Base->Taxes;
    if(is_object($taxes) && isset($taxes->Tax)) {
      foreach ($taxes->Tax as $tax) {
        $title = $tax->TaxDescription->Text;
        $amount = $tax->Amount;

        if (drupal_strlen($title)/* && drupal_strlen($amount)*/) {
          $output[] = array('label' => $title, 'taxAmount' => $amount);
        }
      }
    }
    return $output;
  }

  public function getRentalDepositDueDates() {
    $items = array();

    if(isset($this->UnitStay->DepositPayments) && isset($this->UnitStay->DepositPayments->GuaranteePayment)) {
      if(is_array($this->UnitStay->DepositPayments->GuaranteePayment) && count($this->UnitStay->DepositPayments->GuaranteePayment)) {
        $output = $this->UnitStay->DepositPayments->GuaranteePayment;
      }
      elseif (is_object($this->UnitStay->DepositPayments->GuaranteePayment)) {
        $output[] = $this->UnitStay->DepositPayments->GuaranteePayment;
      }
      foreach($output as $ind => $payment) {
        if($payment->Type == 'RequiredPayment') {
          $items[] = array(
            'title' => (string) $payment->Description[0]->Text->_,
            'date' => $payment->Deadline->AbsoluteDeadline,
            'amount' => $payment->AmountPercent->Amount
          );
        }
      }
    }
    return $items;
  }

  public function petsAllowed() {
    $allowed = FALSE;
    if(isset($this->UnitStay->Pets)) {
      $policy = $this->UnitStay->Pets->PetsAllowedCode;
      if ($policy = $this->UnitStay->Pets->PetsAllowedCode == "Pets Allowed") {
        $allowed = TRUE;
      }
    }
    return $allowed;
  }

  public function getRequiredChargesTaxes() {}
  public function getOptionalChargesTaxes() {}
  public function getTotalPriceTaxes() {} // UnitStay->Total->Taxes->Amount

  public function getCancellationTerms() {} // UnitStay->CancelPenalties->CancelPenalty->PenaltyDescription
  public function getDepositPayments() {} // UnitStay->DepositPayments->GuaranteePayment[]

  public function getWarnings() {}
  public function getErrors() {}
}