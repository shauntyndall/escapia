<?php
/**
 * @file
 * escapia_wsclient_feeds.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function escapia_wsclient_feeds_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "feeds" && $api == "feeds_importer_default") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function escapia_wsclient_feeds_node_info() {
  $items = array(
    'escapia_unit' => array(
      'name' => t('Escapia Unit'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}

/**
 * Implements hook_default_wsclient_service().
 */
function escapia_wsclient_feeds_default_wsclient_service() {
  $items = array();
  $items['escapia_api'] = entity_import('wsclient_service', '{
    "settings" : [],
    "operations" : {
      "UnitDescriptiveInfo" : {
        "label" : "UnitDescriptiveInfo",
        "result" : {
          "type" : "EVRN_UnitDescriptiveInfoRS",
          "label" : "EVRN_UnitDescriptiveInfoRS"
        },
        "parameter" : { "EVRN_UnitDescriptiveInfoRQ" : { "type" : "EVRN_UnitDescriptiveInfoRQ" } }
      },
      "UnitStay" : {
        "label" : "UnitStay",
        "result" : { "type" : "EVRN_UnitStayRS", "label" : "EVRN_UnitStayRS" },
        "parameter" : { "EVRN_UnitStayRQ" : { "type" : "EVRN_UnitStayRQ" } }
      },
      "UnitRes" : {
        "label" : "UnitRes",
        "result" : { "type" : "UnitResResponseType", "label" : "UnitResResponseType" },
        "parameter" : { "EVRN_UnitResRQ" : { "type" : "UnitResRequestType" } }
      },
      "UnitRead" : {
        "label" : "UnitRead",
        "result" : { "type" : "UnitResResponseType", "label" : "UnitResResponseType" },
        "parameter" : { "EVRN_UnitReadRQ" : { "type" : "EVRN_UnitReadRQ" } }
      },
      "UnitInquiry" : {
        "label" : "UnitInquiry",
        "result" : { "type" : "EVRN_UnitInquiryRS", "label" : "EVRN_UnitInquiryRS" },
        "parameter" : { "EVRN_UnitInquiryRQ" : { "type" : "EVRN_UnitInquiryRQ" } }
      },
      "UnitCalendarAvailBatch" : {
        "label" : "UnitCalendarAvailBatch",
        "result" : {
          "type" : "EVRN_UnitCalendarAvailBatchRSType",
          "label" : "EVRN_UnitCalendarAvailBatchRSType"
        },
        "parameter" : { "EVRN_UnitCalendarAvailBatchRQ" : { "type" : "EVRN_UnitCalendarAvailBatchRQ" } }
      },
      "Campaign" : {
        "label" : "Campaign",
        "result" : { "type" : "EVRN_CampaignRS", "label" : "EVRN_CampaignRS" },
        "parameter" : { "EVRN_CampaignRQ" : { "type" : "EVRN_CampaignRQ" } }
      },
      "PropertyManager" : {
        "label" : "PropertyManager",
        "result" : { "type" : "EVRN_PropertyManagerRS", "label" : "EVRN_PropertyManagerRS" },
        "parameter" : { "EVRN_PropertyManagerRQ" : { "type" : "EVRN_PropertyManagerRQ" } }
      },
      "UnitHold" : {
        "label" : "UnitHold",
        "result" : { "type" : "EVRN_UnitHoldRS", "label" : "EVRN_UnitHoldRS" },
        "parameter" : { "EVRN_UnitHoldRQ" : { "type" : "EVRN_UnitHoldRQ" } }
      },
      "ReservationCancel" : {
        "label" : "ReservationCancel",
        "result" : {
          "type" : "EVRN_ReservationCancelRS",
          "label" : "EVRN_ReservationCancelRS"
        },
        "parameter" : { "EVRN_ReservationCancelRQ" : { "type" : "EVRN_ReservationCancelRQ" } }
      },
      "UnitCalendarAvailExtended" : {
        "label" : "UnitCalendarAvailExtended",
        "result" : {
          "type" : "EVRN_UnitCalendarAvailRS",
          "label" : "EVRN_UnitCalendarAvailRS"
        },
        "parameter" : { "EVRN_UnitCalendarAvailRQ" : { "type" : "EVRN_UnitCalendarAvailRQ" } }
      },
      "ReservationUpdate" : {
        "label" : "ReservationUpdate",
        "result" : {
          "type" : "EVRN_ReservationUpdateRS",
          "label" : "EVRN_ReservationUpdateRS"
        },
        "parameter" : { "EVRN_ReservationUpdateRQ" : { "type" : "EVRN_ReservationUpdateRQ" } }
      },
      "UnitSearch" : {
        "label" : "UnitSearch",
        "result" : { "type" : "EVRN_UnitSearchRS", "label" : "EVRN_UnitSearchRS" },
        "parameter" : { "EVRN_UnitSearchRQ" : { "type" : "EVRN_UnitSearchRQ", "allow null" : 0 } },
        "name" : "UnitSearch"
      },
      "UnitCalendarAvail" : {
        "label" : "UnitCalendarAvail",
        "result" : {
          "type" : "EVRN_UnitCalendarAvailRS",
          "label" : "EVRN_UnitCalendarAvailRS"
        },
        "parameter" : { "EVRN_UnitCalendarAvailRQ" : { "type" : "EVRN_UnitCalendarAvailRQ", "allow null" : 0 } },
        "name" : "UnitCalendarAvail"
      }
    },
    "datatypes" : {
      "EVRN_BaseRQType" : {
        "label" : "EVRN_BaseRQType",
        "property info" : {
          "POS" : { "type" : "list\\u003CSourceType\\u003E" },
          "EchoToken" : { "type" : "text" },
          "TimeStamp" : { "type" : "dateTime" },
          "Target" : { "type" : "anonymous2" },
          "Version" : { "type" : "decimal" },
          "TransactionIdentifier" : { "type" : "text" },
          "SequenceNmbr" : { "type" : "nonNegativeInteger" },
          "TransactionStatusCode" : { "type" : "anonymous3" },
          "RetransmissionIndicator" : { "type" : "boolean" }
        }
      },
      "ArrayOfSourceType" : {
        "label" : "ArrayOfSourceType",
        "property info" : { "Source" : { "type" : "SourceType" } }
      },
      "SourceType" : {
        "label" : "SourceType",
        "property info" : {
          "RequestorID" : { "type" : "RequestorID" },
          "BookingChannel" : { "type" : "BookingChannelType" }
        }
      },
      "RequestorID" : {
        "label" : "RequestorID",
        "property info" : { "ID" : { "type" : "text" }, "MessagePassword" : { "type" : "text" } }
      },
      "BookingChannelType" : {
        "label" : "BookingChannelType",
        "property info" : {
          "CompanyName" : { "type" : "CompanyNameType" },
          "Type" : { "type" : "text" },
          "Primary" : { "type" : "boolean" }
        }
      },
      "CompanyNameType" : {
        "label" : "CompanyNameType",
        "property info" : {
          "_" : { "type" : "text" },
          "CompanyShortName" : { "type" : "text" },
          "TravelSector" : { "type" : "text" },
          "Code" : { "type" : "text" },
          "CodeContext" : { "type" : "text" },
          "Division" : { "type" : "text" },
          "Department" : { "type" : "text" }
        }
      },
      "TravelArrangerType" : {
        "label" : "TravelArrangerType",
        "property info" : {
          "_" : { "type" : "CompanyNameType" },
          "DefaultInd" : { "type" : "boolean" },
          "ShareSynchInd" : { "type" : "anonymous10" },
          "ShareMarketInd" : { "type" : "anonymous11" },
          "TravelArrangerType" : { "type" : "text" },
          "RPH" : { "type" : "text" }
        }
      },
      "CompanyNamePrefType" : {
        "label" : "CompanyNamePrefType",
        "property info" : {
          "_" : { "type" : "CompanyNameType" },
          "PreferLevel" : { "type" : "PreferLevelType" }
        }
      },
      "UnitResRequestType" : {
        "label" : "UnitResRequestType",
        "property info" : {
          "UniqueID" : { "type" : "UniqueID_Type" },
          "UnitReservations" : { "type" : "UnitReservationsType" },
          "ResStatus" : { "type" : "TransactionActionType" }
        }
      },
      "UniqueID_Type" : {
        "label" : "UniqueID_Type",
        "property info" : {
          "CompanyName" : { "type" : "CompanyNameType" },
          "URL" : { "type" : "anyURI" },
          "Type" : { "type" : "text" },
          "Instance" : { "type" : "text" },
          "ID" : { "type" : "text" },
          "ID_Context" : { "type" : "text" }
        }
      },
      "UnitReservationsType" : {
        "label" : "UnitReservationsType",
        "property info" : {
          "UnitReservation" : { "type" : "UnitReservationType" },
          "RoutingHops" : { "type" : "list\\u003CRoutingHopTypeRoutingHop\\u003E" },
          "WrittenConfInst" : { "type" : "WrittenConfInstType" },
          "TPA_Extensions" : { "type" : "TPA_Extensions_Type" }
        }
      },
      "UnitReservationType" : {
        "label" : "UnitReservationType",
        "property info" : {
          "UniqueID" : { "type" : "UniqueID_Type" },
          "UnitStays" : { "type" : "list\\u003CUnitStaysTypeUnitStay\\u003E" },
          "Services" : { "type" : "list\\u003CServicesTypeService\\u003E" },
          "ResGuests" : { "type" : "list\\u003CResGuestsTypeResGuest\\u003E" },
          "ResGlobalInfo" : { "type" : "EVRN_ResGlobalInfoType" },
          "WrittenConfInst" : { "type" : "WrittenConfInstType" },
          "TPA_Extensions" : { "type" : "TPA_Extensions_Type" },
          "RoomStayReservation" : { "type" : "boolean" },
          "CreateDateTime" : { "type" : "dateTime" },
          "CreatorID" : { "type" : "text" },
          "LastModifyDateTime" : { "type" : "dateTime" },
          "LastModifierID" : { "type" : "text" },
          "ResStatus" : { "type" : "text" },
          "SourceCategory" : { "type" : "text" },
          "SourceSubCategory" : { "type" : "text" },
          "CampaignID" : { "type" : "integer" }
        }
      },
      "ArrayOfUnitStaysTypeUnitStay" : {
        "label" : "ArrayOfUnitStaysTypeUnitStay",
        "property info" : { "UnitStay" : { "type" : "UnitStay" } }
      },
      "Reference" : {
        "label" : "Reference",
        "property info" : { "DateTime" : { "type" : "dateTime" } }
      },
      "UnitStayType" : {
        "label" : "UnitStayType",
        "property info" : {
          "UnitRates" : { "type" : "list\\u003CUnitStayTypeUnitRate\\u003E" },
          "GuestCounts" : { "type" : "GuestCountType" },
          "TimeSpan" : { "type" : "DateTimeSpanType" },
          "DepositPayments" : { "type" : "list\\u003CRequiredPaymentsTypeGuaranteePayment\\u003E" },
          "CancelPenalties" : { "type" : "CancelPenaltiesType" },
          "Total" : { "type" : "TotalType" },
          "BasicUnitInfo" : { "type" : "BasicUnitInfoType" },
          "RentalAgreement" : { "type" : "list\\u003CParagraphType\\u003E" },
          "Pets" : { "type" : "PetsPoliciesType" },
          "UnitInsuranceInfo" : { "type" : "UnitInsuranceInfo" },
          "AvailabilityStatus" : { "type" : "RateIndicatorType" },
          "PromotionCode" : { "type" : "text" }
        }
      },
      "UnitInsuranceInfo" : {
        "label" : "UnitInsuranceInfo",
        "property info" : { "DamageWaiverOptions" : { "type" : "list\\u003CDamageWaiverOptionType\\u003E" } }
      },
      "ArrayOfUnitStayTypeUnitRate" : {
        "label" : "ArrayOfUnitStayTypeUnitRate",
        "property info" : { "UnitRate" : { "type" : "UnitRate" } }
      },
      "UnitRate" : {
        "label" : "UnitRate",
        "property info" : {
          "Rates" : { "type" : "list\\u003CEVRN_AmountType\\u003E" },
          "UnitRateDescription" : { "type" : "ParagraphType" },
          "Total" : { "type" : "TotalType" }
        }
      },
      "ArrayOfEVRN_AmountType" : {
        "label" : "ArrayOfEVRN_AmountType",
        "property info" : { "Rate" : { "type" : "EVRN_AmountType" } }
      },
      "EVRN_AmountType" : {
        "label" : "EVRN_AmountType",
        "property info" : {
          "Base" : { "type" : "TotalType" },
          "AdditionalGuestAmounts" : { "type" : "AdditionalGuestAmounts" },
          "Fees" : { "type" : "list\\u003CFeeType\\u003E" },
          "CancelPolicies" : { "type" : "CancelPenaltiesType" },
          "PaymentPolicies" : { "type" : "list\\u003CRequiredPaymentsTypeGuaranteePayment\\u003E" },
          "Discount" : { "type" : "Discount" },
          "Total" : { "type" : "TotalType" },
          "RateDescription" : { "type" : "ParagraphType" },
          "AdditionalCharges" : { "type" : "AdditionalCharges" },
          "AdvanceBookingRestriction" : { "type" : "AdvanceBookingRestriction" },
          "EffectiveDate" : { "type" : "date" },
          "ExpireDate" : { "type" : "date" },
          "AgeQualifyingCode" : { "type" : "text" },
          "MinAge" : { "type" : "integer" },
          "MaxAge" : { "type" : "integer" },
          "AgeTimeUnit" : { "type" : "TimeUnitType" },
          "GuaranteedInd" : { "type" : "boolean" },
          "NumberOfUnits" : { "type" : "integer" },
          "RateTimeUnit" : { "type" : "TimeUnitType" },
          "UnitMultiplier" : { "type" : "positiveInteger" },
          "MinGuestApplicable" : { "type" : "positiveInteger" },
          "MaxGuestApplicable" : { "type" : "positiveInteger" },
          "MinLOS" : { "type" : "nonNegativeInteger" },
          "MaxLOS" : { "type" : "nonNegativeInteger" },
          "StayOverDate" : { "type" : "DayOfWeekType" },
          "AlternateCurrencyInd" : { "type" : "boolean" }
        }
      },
      "AdditionalGuestAmounts" : {
        "label" : "AdditionalGuestAmounts",
        "property info" : {
          "AdditionalGuestAmount" : { "type" : "AdditionalGuestAmountType" },
          "AmountBeforeTax" : { "type" : "decimal" },
          "AmountAfterTax" : { "type" : "decimal" },
          "CurrencyCode" : { "type" : "text" },
          "DecimalPlaces" : { "type" : "nonNegativeInteger" }
        }
      },
      "Discount" : {
        "label" : "Discount",
        "property info" : {
          "AppliesTo" : { "type" : "anonymous141" },
          "ItemRPH" : { "type" : "text" }
        }
      },
      "AdditionalCharges" : {
        "label" : "AdditionalCharges",
        "property info" : {
          "AdditionalCharge" : { "type" : "AdditionalChargeType" },
          "OptionalChargesIndicator" : { "type" : "anonymous458" }
        }
      },
      "AdvanceBookingRestriction" : {
        "label" : "AdvanceBookingRestriction",
        "property info" : {
          "Start" : { "type" : "text" },
          "Duration" : { "type" : "text" },
          "End" : { "type" : "text" },
          "Release" : { "type" : "text" },
          "MinAdvanceBookingOffset" : { "type" : "duration" },
          "MaxAdvanceBookingOffset" : { "type" : "duration" },
          "Mon" : { "type" : "boolean" },
          "Tue" : { "type" : "boolean" },
          "Weds" : { "type" : "boolean" },
          "Thur" : { "type" : "boolean" },
          "Fri" : { "type" : "boolean" },
          "Sat" : { "type" : "boolean" },
          "Sun" : { "type" : "boolean" }
        }
      },
      "TotalType" : {
        "label" : "TotalType",
        "property info" : {
          "Taxes" : { "type" : "TaxesType" },
          "AmountBeforeTax" : { "type" : "decimal" },
          "AmountAfterTax" : { "type" : "decimal" },
          "CurrencyCode" : { "type" : "text" },
          "DecimalPlaces" : { "type" : "nonNegativeInteger" },
          "AdditionalFeesExcludedIndicator" : { "type" : "boolean" }
        }
      },
      "TaxesType" : {
        "label" : "TaxesType",
        "property info" : { "Tax" : { "type" : "TaxType" }, "Amount" : { "type" : "decimal" } }
      },
      "TaxType" : {
        "label" : "TaxType",
        "property info" : {
          "TaxDescription" : { "type" : "ParagraphType" },
          "Type" : { "type" : "AmountDeterminationType" },
          "Code" : { "type" : "text" },
          "Percent" : { "type" : "decimal" },
          "Amount" : { "type" : "decimal" },
          "CurrencyCode" : { "type" : "text" },
          "DecimalPlaces" : { "type" : "nonNegativeInteger" },
          "EffectiveDate" : { "type" : "date" },
          "ExpireDate" : { "type" : "date" },
          "ChargeUnit" : { "type" : "text" },
          "ChargeFrequency" : { "type" : "text" },
          "ChargeUnitExempt" : { "type" : "positiveInteger" },
          "ChargeFrequencyExempt" : { "type" : "positiveInteger" },
          "MaxChargeUnitApplies" : { "type" : "positiveInteger" },
          "MaxChargeFrequencyApplies" : { "type" : "positiveInteger" }
        }
      },
      "ParagraphType" : {
        "label" : "ParagraphType",
        "property info" : {
          "ListItem" : { "type" : "ListItem" },
          "Text" : { "type" : "FormattedTextTextType" },
          "Image" : { "type" : "text" },
          "URL" : { "type" : "anyURI" },
          "Name" : { "type" : "text" },
          "ParagraphNumber" : { "type" : "nonNegativeInteger" },
          "CreateDateTime" : { "type" : "dateTime" },
          "CreatorID" : { "type" : "text" },
          "LastModifyDateTime" : { "type" : "dateTime" },
          "LastModifierID" : { "type" : "text" },
          "Language" : { "type" : "language" }
        }
      },
      "ListItem" : {
        "label" : "ListItem",
        "property info" : {
          "_" : { "type" : "FormattedTextTextType" },
          "ListItem" : { "type" : "integer" }
        }
      },
      "FormattedTextTextType" : {
        "label" : "FormattedTextTextType",
        "property info" : {
          "_" : { "type" : "text" },
          "Formatted" : { "type" : "boolean" },
          "Language" : { "type" : "language" }
        }
      },
      "DiscountType" : {
        "label" : "DiscountType",
        "property info" : {
          "DiscountReason" : { "type" : "ParagraphType" },
          "TaxInclusive" : { "type" : "boolean" },
          "Percent" : { "type" : "decimal" },
          "DiscountCode" : { "type" : "text" }
        }
      },
      "RateDiscountType" : {
        "label" : "RateDiscountType",
        "property info" : {
          "MinAdvanceBookingOffset" : { "type" : "duration" },
          "MaxAdvanceBookingOffset" : { "type" : "duration" }
        }
      },
      "AdditionalGuestAmountType" : {
        "label" : "AdditionalGuestAmountType",
        "property info" : {
          "Amount" : { "type" : "TotalType" },
          "AddlGuestAmtDescription" : { "type" : "ParagraphType" },
          "MaxAdditionalGuests" : { "type" : "integer" },
          "AgeQualifyingCode" : { "type" : "text" },
          "MinAge" : { "type" : "integer" },
          "MaxAge" : { "type" : "integer" },
          "AgeTimeUnit" : { "type" : "TimeUnitType" },
          "Type" : { "type" : "text" },
          "Percent" : { "type" : "decimal" },
          "RPH" : { "type" : "text" }
        }
      },
      "ArrayOfFeeType" : {
        "label" : "ArrayOfFeeType",
        "property info" : { "Fee" : { "type" : "FeeType" } }
      },
      "FeeType" : {
        "label" : "FeeType",
        "property info" : {
          "Taxes" : { "type" : "TaxesType" },
          "Description" : { "type" : "ParagraphType" },
          "TaxInclusive" : { "type" : "boolean" },
          "Type" : { "type" : "AmountDeterminationType" },
          "Code" : { "type" : "text" },
          "Percent" : { "type" : "decimal" },
          "Amount" : { "type" : "decimal" },
          "CurrencyCode" : { "type" : "text" },
          "DecimalPlaces" : { "type" : "nonNegativeInteger" },
          "EffectiveDate" : { "type" : "date" },
          "ExpireDate" : { "type" : "date" },
          "MandatoryIndicator" : { "type" : "boolean" },
          "RPH" : { "type" : "text" },
          "ChargeUnit" : { "type" : "text" },
          "ChargeFrequency" : { "type" : "text" },
          "ChargeUnitExempt" : { "type" : "positiveInteger" },
          "ChargeFrequencyExempt" : { "type" : "positiveInteger" },
          "MaxChargeUnitApplies" : { "type" : "positiveInteger" },
          "MaxChargeFrequencyApplies" : { "type" : "positiveInteger" },
          "TaxableIndicator" : { "type" : "boolean" }
        }
      },
      "CommissionPolicyType" : {
        "label" : "CommissionPolicyType",
        "property info" : {
          "MinAdvanceBookingOffset" : { "type" : "duration" },
          "MaxAdvanceBookingOffset" : { "type" : "duration" }
        }
      },
      "CancelPenaltiesType" : {
        "label" : "CancelPenaltiesType",
        "property info" : {
          "CancelPenalty" : { "type" : "CancelPenaltyType" },
          "CancelPolicyIndicator" : { "type" : "boolean" }
        }
      },
      "CancelPenaltyType" : {
        "label" : "CancelPenaltyType",
        "property info" : {
          "Deadline" : { "type" : "Deadline" },
          "AmountPercent" : { "type" : "AmountPercentType" },
          "PenaltyDescription" : { "type" : "ParagraphType" },
          "ConfirmClassCode" : { "type" : "text" },
          "PolicyCode" : { "type" : "text" },
          "NonRefundable" : { "type" : "boolean" },
          "Mon" : { "type" : "boolean" },
          "Tue" : { "type" : "boolean" },
          "Weds" : { "type" : "boolean" },
          "Thur" : { "type" : "boolean" },
          "Fri" : { "type" : "boolean" },
          "Sat" : { "type" : "boolean" },
          "Sun" : { "type" : "boolean" },
          "Start" : { "type" : "text" },
          "Duration" : { "type" : "text" },
          "End" : { "type" : "text" },
          "Release" : { "type" : "text" },
          "RoomTypeCode" : { "type" : "text" }
        }
      },
      "Deadline" : {
        "label" : "Deadline",
        "property info" : {
          "AbsoluteDeadline" : { "type" : "text" },
          "OffsetTimeUnit" : { "type" : "TimeUnitType" },
          "OffsetUnitMultiplier" : { "type" : "integer" },
          "OffsetDropTime" : { "type" : "anonymous150" }
        }
      },
      "AmountPercentType" : {
        "label" : "AmountPercentType",
        "property info" : {
          "Taxes" : { "type" : "TaxesType" },
          "TaxInclusive" : { "type" : "boolean" },
          "FeesInclusive" : { "type" : "boolean" },
          "NmbrOfNights" : { "type" : "nonNegativeInteger" },
          "BasisType" : { "type" : "anonymous51" },
          "Percent" : { "type" : "decimal" },
          "Amount" : { "type" : "decimal" }
        }
      },
      "ArrayOfRequiredPaymentsTypeGuaranteePayment" : {
        "label" : "ArrayOfRequiredPaymentsTypeGuaranteePayment",
        "property info" : { "GuaranteePayment" : { "type" : "GuaranteePayment" } }
      },
      "GuaranteePayment" : {
        "label" : "GuaranteePayment",
        "property info" : {
          "AcceptedPayments" : { "type" : "list\\u003CPaymentFormType\\u003E" },
          "AmountPercent" : { "type" : "AmountPercentType" },
          "Deadline" : { "type" : "Deadline" },
          "Description" : { "type" : "ParagraphType" },
          "Address" : { "type" : "Address" },
          "TPA_Extensions" : { "type" : "TPA_Extensions_Type" },
          "RetributionType" : { "type" : "anonymous57" },
          "PaymentCode" : { "type" : "text" },
          "Type" : { "type" : "anonymous58" },
          "GuaranteeCode" : { "type" : "text" },
          "GuaranteeType" : { "type" : "anonymous59" },
          "HoldTime" : { "type" : "time" },
          "Mon" : { "type" : "boolean" },
          "Tue" : { "type" : "boolean" },
          "Weds" : { "type" : "boolean" },
          "Thur" : { "type" : "boolean" },
          "Fri" : { "type" : "boolean" },
          "Sat" : { "type" : "boolean" },
          "Sun" : { "type" : "boolean" },
          "Start" : { "type" : "text" },
          "Duration" : { "type" : "text" },
          "End" : { "type" : "text" },
          "Release" : { "type" : "text" },
          "NoCardHolderInfoReqInd" : { "type" : "boolean" },
          "NameInd" : { "type" : "boolean" },
          "AddressInd" : { "type" : "boolean" },
          "PhoneInd" : { "type" : "boolean" },
          "InterbankNbrInd" : { "type" : "boolean" },
          "RoomTypeCode" : { "type" : "text" },
          "InfoSource" : { "type" : "text" },
          "NonRefundableIndicator" : { "type" : "boolean" }
        }
      },
      "Address" : {
        "label" : "Address",
        "property info" : { "SameCountryInd" : { "type" : "boolean" } }
      },
      "ArrayOfPaymentFormType" : {
        "label" : "ArrayOfPaymentFormType",
        "property info" : { "AcceptedPayment" : { "type" : "PaymentFormType" } }
      },
      "PaymentFormType" : {
        "label" : "PaymentFormType",
        "property info" : {
          "PaymentCard" : { "type" : "PaymentCardType" },
          "DirectBill" : { "type" : "DirectBillType" },
          "LoyaltyRedemption" : { "type" : "LoyaltyRedemption" },
          "MiscChargeOrder" : { "type" : "MiscChargeOrder" },
          "BankAcct" : { "type" : "BankAcctType" },
          "Voucher" : { "type" : "Voucher" },
          "Cash" : { "type" : "Cash" },
          "ShareSynchInd" : { "type" : "anonymous67" },
          "ShareMarketInd" : { "type" : "anonymous68" },
          "CostCenterID" : { "type" : "text" },
          "RPH" : { "type" : "text" },
          "PaymentTransactionTypeCode" : { "type" : "anonymous69" }
        }
      },
      "LoyaltyRedemption" : {
        "label" : "LoyaltyRedemption",
        "property info" : {
          "CertificateNumber" : { "type" : "text" },
          "MemberNumber" : { "type" : "text" },
          "ProgramName" : { "type" : "text" },
          "LoyaltyVendorCode" : { "type" : "text" },
          "PromotionCode" : { "type" : "text" },
          "PromotionVendorCode" : { "type" : "anonymous63" },
          "RedemptionQuantity" : { "type" : "positiveInteger" }
        }
      },
      "MiscChargeOrder" : {
        "label" : "MiscChargeOrder",
        "property info" : { "TicketNumber" : { "type" : "text" } }
      },
      "Voucher" : {
        "label" : "Voucher",
        "property info" : { "SeriesCode" : { "type" : "text" } }
      },
      "Cash" : {
        "label" : "Cash",
        "property info" : { "CashIndicator" : { "type" : "boolean" } }
      },
      "PaymentCardType" : {
        "label" : "PaymentCardType",
        "property info" : {
          "CardHolderName" : { "type" : "text" },
          "CardIssuerName" : { "type" : "CardIssuerName" },
          "Address" : { "type" : "AddressType" },
          "ShareSynchInd" : { "type" : "anonymous72" },
          "ShareMarketInd" : { "type" : "anonymous73" },
          "CardType" : { "type" : "text" },
          "CardCode" : { "type" : "text" },
          "CardNumber" : { "type" : "text" },
          "SeriesCode" : { "type" : "text" },
          "EffectiveDate" : { "type" : "text" },
          "ExpireDate" : { "type" : "text" },
          "MaskedCardNumber" : { "type" : "text" },
          "CardHolderRPH" : { "type" : "text" },
          "CardToken" : { "type" : "text" }
        }
      },
      "CardIssuerName" : {
        "label" : "CardIssuerName",
        "property info" : { "BankID" : { "type" : "text" } }
      },
      "AddressType" : {
        "label" : "AddressType",
        "property info" : {
          "StreetNmbr" : { "type" : "StreetNmbr" },
          "BldgRoom" : { "type" : "BldgRoom" },
          "AddressLine" : { "type" : "text" },
          "CityName" : { "type" : "text" },
          "PostalCode" : { "type" : "text" },
          "County" : { "type" : "text" },
          "StateProv" : { "type" : "StateProvType" },
          "CountryName" : { "type" : "CountryNameType" },
          "FormattedInd" : { "type" : "boolean" },
          "ShareSynchInd" : { "type" : "anonymous77" },
          "ShareMarketInd" : { "type" : "anonymous78" },
          "Type" : { "type" : "text" }
        }
      },
      "StreetNmbr" : {
        "label" : "StreetNmbr",
        "property info" : {
          "_" : { "type" : "StreetNmbrType" },
          "StreetNmbrSuffix" : { "type" : "text" },
          "StreetDirection" : { "type" : "text" },
          "RuralRouteNmbr" : { "type" : "text" }
        }
      },
      "BldgRoom" : {
        "label" : "BldgRoom",
        "property info" : {
          "_" : { "type" : "text" },
          "BldgNameIndicator" : { "type" : "boolean" }
        }
      },
      "StreetNmbrType" : {
        "label" : "StreetNmbrType",
        "property info" : { "_" : { "type" : "text" }, "PO_Box" : { "type" : "text" } }
      },
      "StateProvType" : {
        "label" : "StateProvType",
        "property info" : { "_" : { "type" : "text" }, "StateCode" : { "type" : "text" } }
      },
      "CountryNameType" : {
        "label" : "CountryNameType",
        "property info" : { "_" : { "type" : "text" }, "Code" : { "type" : "text" } }
      },
      "AddressInfoType" : {
        "label" : "AddressInfoType",
        "property info" : {
          "DefaultInd" : { "type" : "boolean" },
          "UseType" : { "type" : "text" },
          "RPH" : { "type" : "text" }
        }
      },
      "DirectBillType" : {
        "label" : "DirectBillType",
        "property info" : {
          "CompanyName" : { "type" : "CompanyName" },
          "Address" : { "type" : "AddressInfoType" },
          "ShareSynchInd" : { "type" : "anonymous85" },
          "ShareMarketInd" : { "type" : "anonymous86" },
          "DirectBill_ID" : { "type" : "text" }
        }
      },
      "CompanyName" : {
        "label" : "CompanyName",
        "property info" : {
          "_" : { "type" : "CompanyNameType" },
          "ContactName" : { "type" : "text" }
        }
      },
      "BankAcctType" : {
        "label" : "BankAcctType",
        "property info" : {
          "BankAcctName" : { "type" : "text" },
          "AcctHolderName" : { "type" : "text" },
          "Address" : { "type" : "AddressType" },
          "ShareSynchInd" : { "type" : "anonymous88" },
          "ShareMarketInd" : { "type" : "anonymous89" },
          "BankID" : { "type" : "text" },
          "AcctType" : { "type" : "text" },
          "BankAcctNumber" : { "type" : "text" },
          "ChecksAcceptedInd" : { "type" : "boolean" },
          "AcctNumberToken" : { "type" : "text" },
          "MaskedAcctNumber" : { "type" : "text" },
          "RoutingNumberToken" : { "type" : "text" },
          "MaskedRoutingNumber" : { "type" : "text" }
        }
      },
      "TPA_Extensions_Type" : {
        "label" : "TPA_Extensions_Type",
        "property info" : { "any" : { "type" : "\\u003CanyXML\\u003E" } }
      },
      "AdditionalChargeType" : {
        "label" : "AdditionalChargeType",
        "property info" : {
          "Amount" : { "type" : "TotalType" },
          "Description" : { "type" : "ParagraphType" },
          "Code" : { "type" : "text" },
          "ChargeTemplateID" : { "type" : "integer" },
          "Quantity" : { "type" : "nonNegativeInteger" }
        }
      },
      "GuestCountType" : {
        "label" : "GuestCountType",
        "property info" : {
          "GuestCount" : { "type" : "GuestCount" },
          "IsPerRoom" : { "type" : "boolean" }
        }
      },
      "GuestCount" : {
        "label" : "GuestCount",
        "property info" : {
          "AgeQualifyingCode" : { "type" : "text" },
          "Age" : { "type" : "integer" },
          "Count" : { "type" : "integer" }
        }
      },
      "StartDateWindow" : {
        "label" : "StartDateWindow",
        "property info" : {
          "EarliestDate" : { "type" : "text" },
          "LatestDate" : { "type" : "text" },
          "DOW" : { "type" : "DayOfWeekType" }
        }
      },
      "EndDateWindow" : {
        "label" : "EndDateWindow",
        "property info" : {
          "EarliestDate" : { "type" : "text" },
          "LatestDate" : { "type" : "text" },
          "DOW" : { "type" : "DayOfWeekType" }
        }
      },
      "TimeInstantType" : {
        "label" : "TimeInstantType",
        "property info" : {
          "_" : { "type" : "text" },
          "WindowBefore" : { "type" : "duration" },
          "WindowAfter" : { "type" : "duration" },
          "CrossDateAllowedIndicator" : { "type" : "boolean" }
        }
      },
      "BasicUnitInfoType" : {
        "label" : "BasicUnitInfoType",
        "property info" : {
          "VendorMessages" : { "type" : "list\\u003CVendorMessageType\\u003E" },
          "Position" : { "type" : "Position" },
          "Address" : { "type" : "AddressInfoType" },
          "ContactNumbers" : { "type" : "list\\u003CBasicUnitInfoTypeContactNumber\\u003E" },
          "Award" : { "type" : "Award" },
          "UnitAmenity" : { "type" : "UnitAmenityType" },
          "UnitSummary" : { "type" : "UnitStayCandidateType" },
          "PropertyManagerCode" : { "type" : "text" },
          "UnitCode" : { "type" : "text" },
          "UnitName" : { "type" : "text" },
          "InfoSource" : { "type" : "text" },
          "InternalUnitCode" : { "type" : "text" },
          "UnitHeadline" : { "type" : "text" },
          "PropertyURL" : { "type" : "text" },
          "UnitClassCode" : { "type" : "text" }
        }
      },
      "Position" : {
        "label" : "Position",
        "property info" : {
          "Latitude" : { "type" : "text" },
          "Longitude" : { "type" : "text" },
          "Altitude" : { "type" : "text" },
          "AltitudeUnitOfMeasureCode" : { "type" : "text" }
        }
      },
      "Award" : {
        "label" : "Award",
        "property info" : { "Provider" : { "type" : "text" }, "Rating" : { "type" : "text" } }
      },
      "ArrayOfVendorMessageType" : {
        "label" : "ArrayOfVendorMessageType",
        "property info" : { "VendorMessage" : { "type" : "VendorMessageType" } }
      },
      "VendorMessageType" : {
        "label" : "VendorMessageType",
        "property info" : { "InfoType" : { "type" : "text" } }
      },
      "FormattedTextType" : {
        "label" : "FormattedTextType",
        "property info" : {
          "SubSection" : { "type" : "FormattedTextSubSectionType" },
          "Title" : { "type" : "text" },
          "Language" : { "type" : "language" }
        }
      },
      "FormattedTextSubSectionType" : {
        "label" : "FormattedTextSubSectionType",
        "property info" : {
          "Paragraph" : { "type" : "ParagraphType" },
          "SubTitle" : { "type" : "text" },
          "SubCode" : { "type" : "text" },
          "SubSectionNumber" : { "type" : "integer" }
        }
      },
      "ArrayOfBasicUnitInfoTypeContactNumber" : {
        "label" : "ArrayOfBasicUnitInfoTypeContactNumber",
        "property info" : { "ContactNumber" : { "type" : "ContactNumber" } }
      },
      "ContactNumber" : {
        "label" : "ContactNumber",
        "property info" : {
          "ShareSynchInd" : { "type" : "anonymous108" },
          "ShareMarketInd" : { "type" : "anonymous109" },
          "PhoneLocationType" : { "type" : "text" },
          "PhoneTechType" : { "type" : "text" },
          "PhoneUseType" : { "type" : "text" },
          "CountryAccessCode" : { "type" : "text" },
          "AreaCityCode" : { "type" : "text" },
          "PhoneNumber" : { "type" : "text" },
          "Extension" : { "type" : "text" },
          "PIN" : { "type" : "text" },
          "FormattedInd" : { "type" : "boolean" },
          "DefaultInd" : { "type" : "boolean" },
          "RPH" : { "type" : "text" }
        }
      },
      "UnitAmenityType" : {
        "label" : "UnitAmenityType",
        "property info" : { "Code" : { "type" : "text" }, "Quantity" : { "type" : "unsignedInt" } }
      },
      "UnitStayCandidateType" : {
        "label" : "UnitStayCandidateType",
        "property info" : {
          "RoomCounts" : { "type" : "list\\u003CRoomCountType\\u003E" },
          "BedCounts" : { "type" : "list\\u003CBedCountType\\u003E" },
          "GuestCounts" : { "type" : "GuestCountType" },
          "PetsPolicies" : { "type" : "PetsPoliciesType" },
          "NumberFloors" : { "type" : "integer" },
          "NonSmoking" : { "type" : "boolean" },
          "AreaSquareFeet" : { "type" : "integer" },
          "MaxOccupancy" : { "type" : "integer" },
          "WhenBuilt" : { "type" : "date" }
        }
      },
      "ArrayOfRoomCountType" : {
        "label" : "ArrayOfRoomCountType",
        "property info" : { "RoomCount" : { "type" : "RoomCountType" } }
      },
      "RoomCountType" : {
        "label" : "RoomCountType",
        "property info" : {
          "Code" : { "type" : "text" },
          "Min" : { "type" : "decimal" },
          "Max" : { "type" : "decimal" },
          "Fixed" : { "type" : "decimal" }
        }
      },
      "ArrayOfBedCountType" : {
        "label" : "ArrayOfBedCountType",
        "property info" : { "BedCount" : { "type" : "BedCountType" } }
      },
      "BedCountType" : {
        "label" : "BedCountType",
        "property info" : {
          "Code" : { "type" : "text" },
          "Min" : { "type" : "unsignedByte" },
          "Max" : { "type" : "unsignedByte" },
          "Fixed" : { "type" : "unsignedByte" }
        }
      },
      "PetsPoliciesType" : {
        "label" : "PetsPoliciesType",
        "property info" : {
          "PetsPolicy" : { "type" : "PetsPolicy" },
          "PetsAllowedCode" : { "type" : "PetsAllowedCodeType" }
        }
      },
      "PetsPolicy" : {
        "label" : "PetsPolicy",
        "property info" : { "Code" : { "type" : "text" } }
      },
      "UnitValueMatchType" : {
        "label" : "UnitValueMatchType",
        "property info" : {
          "RateRange" : { "type" : "RateRange" },
          "LastMinuteDiscountRange" : { "type" : "LastMinuteDiscountRangeType" },
          "MoreDataEchoToken" : { "type" : "text" },
          "SameCountryInd" : { "type" : "boolean" },
          "AvailabilityStatus" : { "type" : "RateIndicatorType" }
        }
      },
      "RateRange" : {
        "label" : "RateRange",
        "property info" : {
          "RoomStayCandidateRPH" : { "type" : "text" },
          "RateType" : { "type" : "RateTypeType" },
          "MinRate" : { "type" : "decimal" },
          "MaxRate" : { "type" : "decimal" },
          "FixedRate" : { "type" : "decimal" },
          "FullRate" : { "type" : "decimal" },
          "RateTimeUnit" : { "type" : "TimeUnitType" },
          "MinRent" : { "type" : "decimal" },
          "MaxRent" : { "type" : "decimal" },
          "FixedRent" : { "type" : "decimal" },
          "FullRent" : { "type" : "decimal" },
          "MinFees" : { "type" : "decimal" },
          "MaxFees" : { "type" : "decimal" },
          "FixedFees" : { "type" : "decimal" },
          "FullFees" : { "type" : "decimal" },
          "MinTax" : { "type" : "decimal" },
          "MaxTax" : { "type" : "decimal" },
          "FixedTax" : { "type" : "decimal" },
          "FullTax" : { "type" : "decimal" }
        }
      },
      "LastMinuteDiscountRangeType" : {
        "label" : "LastMinuteDiscountRangeType",
        "property info" : {
          "MinAdvanceBookingOffset" : { "type" : "duration" },
          "MaxAdvanceBookingOffset" : { "type" : "duration" },
          "MinDiscountPercent" : { "type" : "decimal" },
          "MaxDiscountPercent" : { "type" : "decimal" }
        }
      },
      "ArrayOfParagraphType" : {
        "label" : "ArrayOfParagraphType",
        "property info" : { "Description" : { "type" : "ParagraphType" } }
      },
      "ArrayOfDamageWaiverOptionType" : {
        "label" : "ArrayOfDamageWaiverOptionType",
        "property info" : { "DamageWaiverOption" : { "type" : "DamageWaiverOptionType" } }
      },
      "DamageWaiverOptionType" : {
        "label" : "DamageWaiverOptionType",
        "property info" : {
          "Coverage" : { "type" : "Coverage" },
          "ChargeTemplateID" : { "type" : "integer" }
        }
      },
      "Coverage" : {
        "label" : "Coverage",
        "property info" : { "Amount" : { "type" : "decimal" } }
      },
      "ArrayOfResGuestRPHsTypeResGuestRPH" : {
        "label" : "ArrayOfResGuestRPHsTypeResGuestRPH",
        "property info" : { "ResGuestRPH" : { "type" : "ResGuestRPH" } }
      },
      "ResGuestRPH" : {
        "label" : "ResGuestRPH",
        "property info" : { "RPH" : { "type" : "text" } }
      },
      "ArrayOfCommentTypeComment" : {
        "label" : "ArrayOfCommentTypeComment",
        "property info" : { "Comment" : { "type" : "Comment" } }
      },
      "Comment" : {
        "label" : "Comment",
        "property info" : {
          "CommentOriginatorCode" : { "type" : "text" },
          "GuestViewable" : { "type" : "boolean" }
        }
      },
      "ArrayOfSpecialRequestTypeSpecialRequest" : {
        "label" : "ArrayOfSpecialRequestTypeSpecialRequest",
        "property info" : { "SpecialRequest" : { "type" : "SpecialRequest" } }
      },
      "SpecialRequest" : {
        "label" : "SpecialRequest",
        "property info" : {
          "RequestCode" : { "type" : "text" },
          "CodeContext" : { "type" : "text" },
          "NumberOfUnits" : { "type" : "integer" }
        }
      },
      "ArrayOfServiceRPHsTypeServiceRPH" : {
        "label" : "ArrayOfServiceRPHsTypeServiceRPH",
        "property info" : { "ServiceRPH" : { "type" : "ServiceRPH" } }
      },
      "ServiceRPH" : {
        "label" : "ServiceRPH",
        "property info" : { "RPH" : { "type" : "text" }, "IsPerRoom" : { "type" : "boolean" } }
      },
      "ArrayOfServicesTypeService" : {
        "label" : "ArrayOfServicesTypeService",
        "property info" : { "Service" : { "type" : "Service" } }
      },
      "Service" : {
        "label" : "Service",
        "property info" : {
          "RelativePosition" : { "type" : "RelativePositionType" },
          "OperationSchedules" : { "type" : "list\\u003COperationSchedulesPlusChargeTypeOperationSchedule\\u003E" },
          "MultimediaDescriptions" : { "type" : "MultimediaDescriptionsType" },
          "Features" : { "type" : "list\\u003CFeaturesTypeFeature\\u003E" },
          "DescriptiveText" : { "type" : "DescriptiveText" },
          "Included" : { "type" : "boolean" },
          "Code" : { "type" : "text" },
          "BusinessServiceCode" : { "type" : "text" },
          "ExistsCode" : { "type" : "text" },
          "CodeDetail" : { "type" : "text" },
          "AvailableToAnyGuest" : { "type" : "boolean" },
          "InvCode" : { "type" : "text" },
          "ProximityCode" : { "type" : "text" },
          "MealPlanCode" : { "type" : "text" },
          "Quantity" : { "type" : "nonNegativeInteger" },
          "Sort" : { "type" : "nonNegativeInteger" },
          "MeetingRoomCode" : { "type" : "text" }
        }
      },
      "AmountType" : {
        "label" : "AmountType",
        "property info" : {
          "Base" : { "type" : "TotalType" },
          "AdditionalGuestAmounts" : { "type" : "AdditionalGuestAmounts" },
          "Fees" : { "type" : "list\\u003CFeeType\\u003E" },
          "CancelPolicies" : { "type" : "CancelPenaltiesType" },
          "PaymentPolicies" : { "type" : "list\\u003CRequiredPaymentsTypeGuaranteePayment\\u003E" },
          "Discount" : { "type" : "Discount" },
          "Total" : { "type" : "TotalType" },
          "RateDescription" : { "type" : "ParagraphType" },
          "AdditionalCharges" : { "type" : "AdditionalCharges" },
          "AdvanceBookingRestriction" : { "type" : "AdvanceBookingRestriction" },
          "EffectiveDate" : { "type" : "date" },
          "ExpireDate" : { "type" : "date" },
          "AgeQualifyingCode" : { "type" : "text" },
          "MinAge" : { "type" : "integer" },
          "MaxAge" : { "type" : "integer" },
          "AgeTimeUnit" : { "type" : "TimeUnitType" },
          "GuaranteedInd" : { "type" : "boolean" },
          "NumberOfUnits" : { "type" : "integer" },
          "RateTimeUnit" : { "type" : "TimeUnitType" },
          "UnitMultiplier" : { "type" : "positiveInteger" },
          "MinGuestApplicable" : { "type" : "positiveInteger" },
          "MaxGuestApplicable" : { "type" : "positiveInteger" },
          "MinLOS" : { "type" : "nonNegativeInteger" },
          "MaxLOS" : { "type" : "nonNegativeInteger" },
          "StayOverDate" : { "type" : "DayOfWeekType" },
          "AlternateCurrencyInd" : { "type" : "boolean" }
        }
      },
      "AdditionalCharge" : {
        "label" : "AdditionalCharge",
        "property info" : {
          "Amount" : { "type" : "TotalType" },
          "RoomAmenityCode" : { "type" : "text" },
          "Quantity" : { "type" : "nonNegativeInteger" }
        }
      },
      "ResCommonDetailType" : {
        "label" : "ResCommonDetailType",
        "property info" : {
          "GuestCounts" : { "type" : "GuestCountType" },
          "TimeSpan" : { "type" : "DateTimeSpanType" },
          "ResGuestRPHs" : { "type" : "list\\u003CResGuestRPHsTypeResGuestRPH\\u003E" },
          "Memberships" : { "type" : "list\\u003CMembershipTypeMembership\\u003E" },
          "Comments" : { "type" : "list\\u003CCommentTypeComment\\u003E" },
          "SpecialRequests" : { "type" : "list\\u003CSpecialRequestTypeSpecialRequest\\u003E" },
          "Guarantee" : { "type" : "GuaranteeType" },
          "DepositPayments" : { "type" : "list\\u003CRequiredPaymentsTypeGuaranteePayment\\u003E" },
          "CancelPenalties" : { "type" : "CancelPenaltiesType" },
          "Fees" : { "type" : "list\\u003CFeeType\\u003E" },
          "Total" : { "type" : "TotalType" }
        }
      },
      "ArrayOfMembershipTypeMembership" : {
        "label" : "ArrayOfMembershipTypeMembership",
        "property info" : { "Membership" : { "type" : "Membership" } }
      },
      "Membership" : {
        "label" : "Membership",
        "property info" : {
          "ProgramCode" : { "type" : "text" },
          "BonusCode" : { "type" : "text" },
          "AccountID" : { "type" : "text" },
          "PointsEarned" : { "type" : "integer" },
          "TravelSector" : { "type" : "text" }
        }
      },
      "GuaranteeType" : {
        "label" : "GuaranteeType",
        "property info" : {
          "GuaranteesAccepted" : { "type" : "list\\u003CGuaranteeTypeGuaranteeAccepted\\u003E" },
          "Deadline" : { "type" : "Deadline" },
          "Comments" : { "type" : "list\\u003CCommentTypeComment\\u003E" },
          "GuaranteeDescription" : { "type" : "ParagraphType" },
          "RetributionType" : { "type" : "anonymous151" },
          "GuaranteeCode" : { "type" : "text" },
          "GuaranteeType" : { "type" : "anonymous152" },
          "HoldTime" : { "type" : "time" }
        }
      },
      "ArrayOfGuaranteeTypeGuaranteeAccepted" : {
        "label" : "ArrayOfGuaranteeTypeGuaranteeAccepted",
        "property info" : { "GuaranteeAccepted" : { "type" : "GuaranteeAccepted" } }
      },
      "GuaranteeAccepted" : {
        "label" : "GuaranteeAccepted",
        "property info" : {
          "Default" : { "type" : "boolean" },
          "NoCardHolderInfoReqInd" : { "type" : "boolean" },
          "NameReqInd" : { "type" : "boolean" },
          "AddressReqInd" : { "type" : "boolean" },
          "PhoneReqInd" : { "type" : "boolean" },
          "InterbankNbrReqInd" : { "type" : "boolean" },
          "BookingSourceAllowedInd" : { "type" : "boolean" },
          "CorpDiscountNbrAllowedInd" : { "type" : "boolean" },
          "GuaranteeTypeCode" : { "type" : "text" },
          "GuaranteeID" : { "type" : "text" }
        }
      },
      "ResGlobalInfoType" : {
        "label" : "ResGlobalInfoType",
        "property info" : {
          "HotelReservationIDs" : { "type" : "list\\u003CHotelReservationIDsTypeHotelReservationID\\u003E" },
          "RoutingHops" : { "type" : "list\\u003CRoutingHopTypeRoutingHop\\u003E" },
          "Profiles" : { "type" : "list\\u003CProfilesTypeProfileInfo\\u003E" }
        }
      },
      "ArrayOfHotelReservationIDsTypeHotelReservationID" : {
        "label" : "ArrayOfHotelReservationIDsTypeHotelReservationID",
        "property info" : { "HotelReservationID" : { "type" : "HotelReservationID" } }
      },
      "HotelReservationID" : {
        "label" : "HotelReservationID",
        "property info" : {
          "ResID_Type" : { "type" : "text" },
          "ResID_Value" : { "type" : "text" },
          "ResID_Source" : { "type" : "text" },
          "ResID_SourceContext" : { "type" : "text" },
          "ResID_Date" : { "type" : "dateTime" },
          "ForGuest" : { "type" : "boolean" },
          "ResGuestRPH" : { "type" : "text" },
          "CancelOriginatorCode" : { "type" : "text" },
          "CancellationDate" : { "type" : "dateTime" }
        }
      },
      "ArrayOfRoutingHopTypeRoutingHop" : {
        "label" : "ArrayOfRoutingHopTypeRoutingHop",
        "property info" : { "RoutingHop" : { "type" : "RoutingHop" } }
      },
      "RoutingHop" : {
        "label" : "RoutingHop",
        "property info" : {
          "SystemCode" : { "type" : "text" },
          "LocalRefID" : { "type" : "text" },
          "TimeStamp" : { "type" : "dateTime" },
          "Comment" : { "type" : "text" },
          "SequenceNmbr" : { "type" : "integer" },
          "Data" : { "type" : "text" }
        }
      },
      "ArrayOfProfilesTypeProfileInfo" : {
        "label" : "ArrayOfProfilesTypeProfileInfo",
        "property info" : { "ProfileInfo" : { "type" : "ProfileInfo" } }
      },
      "ProfileInfo" : {
        "label" : "ProfileInfo",
        "property info" : {
          "UniqueID" : { "type" : "UniqueID_Type" },
          "Profile" : { "type" : "ProfileType" }
        }
      },
      "ProfileType" : {
        "label" : "ProfileType",
        "property info" : {
          "Accesses" : { "type" : "AccessesType" },
          "Customer" : { "type" : "CustomerType" },
          "PrefCollections" : { "type" : "PreferencesType" },
          "CompanyInfo" : { "type" : "CompanyInfoType" },
          "Affiliations" : { "type" : "AffiliationsType" },
          "Agreements" : { "type" : "AgreementsType" },
          "TPA_Extensions" : { "type" : "TPA_Extensions_Type" },
          "ShareAllSynchInd" : { "type" : "YesNoType" },
          "ShareAllMarketInd" : { "type" : "YesNoType" },
          "ProfileType" : { "type" : "text" },
          "CreateDateTime" : { "type" : "dateTime" },
          "CreatorID" : { "type" : "text" },
          "LastModifyDateTime" : { "type" : "dateTime" },
          "LastModifierID" : { "type" : "text" },
          "RPH" : { "type" : "text" }
        }
      },
      "AccessesType" : {
        "label" : "AccessesType",
        "property info" : {
          "Access" : { "type" : "Access" },
          "ShareSynchInd" : { "type" : "anonymous166" },
          "ShareMarketInd" : { "type" : "anonymous167" },
          "CreateDateTime" : { "type" : "dateTime" }
        }
      },
      "Access" : {
        "label" : "Access",
        "property info" : {
          "AccessPerson" : { "type" : "PersonNameType" },
          "AccessComment" : { "type" : "FreeTextType" },
          "ActionType" : { "type" : "anonymous165" },
          "ActionDateTime" : { "type" : "dateTime" },
          "ID" : { "type" : "text" }
        }
      },
      "PersonNameType" : {
        "label" : "PersonNameType",
        "property info" : {
          "NamePrefix" : { "type" : "text" },
          "GivenName" : { "type" : "text" },
          "MiddleName" : { "type" : "text" },
          "SurnamePrefix" : { "type" : "text" },
          "Surname" : { "type" : "text" },
          "NameSuffix" : { "type" : "text" },
          "NameTitle" : { "type" : "text" },
          "ShareSynchInd" : { "type" : "anonymous169" },
          "ShareMarketInd" : { "type" : "anonymous170" },
          "NameType" : { "type" : "text" }
        }
      },
      "FreeTextType" : {
        "label" : "FreeTextType",
        "property info" : { "_" : { "type" : "text" }, "Language" : { "type" : "language" } }
      },
      "CommissionInfoType" : {
        "label" : "CommissionInfoType",
        "property info" : {
          "_" : { "type" : "FreeTextType" },
          "ShareSynchInd" : { "type" : "anonymous173" },
          "ShareMarketInd" : { "type" : "anonymous174" },
          "CommissionPlanCode" : { "type" : "text" },
          "Amount" : { "type" : "decimal" }
        }
      },
      "ErrorType" : {
        "label" : "ErrorType",
        "property info" : {
          "_" : { "type" : "FreeTextType" },
          "Type" : { "type" : "text" },
          "ShortText" : { "type" : "text" },
          "Code" : { "type" : "text" },
          "Status" : { "type" : "text" },
          "Tag" : { "type" : "text" },
          "RecordID" : { "type" : "text" },
          "NodeList" : { "type" : "text" }
        }
      },
      "WarningType" : {
        "label" : "WarningType",
        "property info" : {
          "_" : { "type" : "FreeTextType" },
          "Type" : { "type" : "text" },
          "ShortText" : { "type" : "text" },
          "Code" : { "type" : "text" },
          "Status" : { "type" : "text" },
          "Tag" : { "type" : "text" },
          "RecordID" : { "type" : "text" }
        }
      },
      "CertificationType" : {
        "label" : "CertificationType",
        "property info" : {
          "_" : { "type" : "FreeTextType" },
          "ID" : { "type" : "text" },
          "SingleVendorInd" : { "type" : "anonymous178" },
          "EffectiveDate" : { "type" : "date" },
          "ExpireDate" : { "type" : "date" }
        }
      },
      "CustomerType" : {
        "label" : "CustomerType",
        "property info" : {
          "PersonName" : { "type" : "PersonNameType" },
          "Telephone" : { "type" : "Telephone" },
          "Email" : { "type" : "EmailType" },
          "Address" : { "type" : "Address" },
          "URL" : { "type" : "URL_Type" },
          "CitizenCountryName" : { "type" : "CitizenCountryName" },
          "PhysChallName" : { "type" : "text" },
          "PetInfo" : { "type" : "text" },
          "PaymentForm" : { "type" : "PaymentFormType" },
          "RelatedTraveler" : { "type" : "RelatedTravelerType" },
          "ContactPerson" : { "type" : "ContactPersonType" },
          "Document" : { "type" : "DocumentType" },
          "CustLoyalty" : { "type" : "CustLoyalty" },
          "EmployeeInfo" : { "type" : "EmployeeInfoType" },
          "EmployerInfo" : { "type" : "CompanyNameType" },
          "TPA_Extensions" : { "type" : "TPA_Extensions_Type" },
          "Gender" : { "type" : "anonymous187" },
          "Deceased" : { "type" : "boolean" },
          "LockoutType" : { "type" : "text" },
          "BirthDate" : { "type" : "date" },
          "CurrencyCode" : { "type" : "text" },
          "DecimalPlaces" : { "type" : "nonNegativeInteger" },
          "VIP_Indicator" : { "type" : "boolean" }
        }
      },
      "Telephone" : {
        "label" : "Telephone",
        "property info" : {
          "ShareSynchInd" : { "type" : "anonymous221" },
          "ShareMarketInd" : { "type" : "anonymous222" },
          "PhoneLocationType" : { "type" : "text" },
          "PhoneTechType" : { "type" : "text" },
          "PhoneUseType" : { "type" : "text" },
          "CountryAccessCode" : { "type" : "text" },
          "AreaCityCode" : { "type" : "text" },
          "PhoneNumber" : { "type" : "text" },
          "Extension" : { "type" : "text" },
          "PIN" : { "type" : "text" },
          "FormattedInd" : { "type" : "boolean" },
          "DefaultInd" : { "type" : "boolean" },
          "RPH" : { "type" : "text" }
        }
      },
      "CitizenCountryName" : {
        "label" : "CitizenCountryName",
        "property info" : { "Code" : { "type" : "text" } }
      },
      "CustLoyalty" : {
        "label" : "CustLoyalty",
        "property info" : {
          "ProgramID" : { "type" : "text" },
          "MembershipID" : { "type" : "text" },
          "TravelSector" : { "type" : "text" },
          "RPH" : { "type" : "text" },
          "VendorCode" : { "type" : "anonymous470" }
        }
      },
      "EmailType" : {
        "label" : "EmailType",
        "property info" : {
          "_" : { "type" : "text" },
          "ShareSynchInd" : { "type" : "anonymous189" },
          "ShareMarketInd" : { "type" : "anonymous190" },
          "DefaultInd" : { "type" : "boolean" },
          "EmailType" : { "type" : "text" },
          "RPH" : { "type" : "text" }
        }
      },
      "URL_Type" : {
        "label" : "URL_Type",
        "property info" : {
          "_" : { "type" : "anyURI" },
          "ShareSynchInd" : { "type" : "anonymous192" },
          "ShareMarketInd" : { "type" : "anonymous193" },
          "Type" : { "type" : "text" },
          "DefaultInd" : { "type" : "boolean" }
        }
      },
      "RelatedTravelerType" : {
        "label" : "RelatedTravelerType",
        "property info" : {
          "UniqueID" : { "type" : "UniqueID_Type" },
          "PersonName" : { "type" : "PersonNameType" },
          "ShareSynchInd" : { "type" : "anonymous195" },
          "ShareMarketInd" : { "type" : "anonymous196" },
          "Relation" : { "type" : "text" }
        }
      },
      "ContactPersonType" : {
        "label" : "ContactPersonType",
        "property info" : {
          "PersonName" : { "type" : "PersonNameType" },
          "Telephone" : { "type" : "Telephone" },
          "Address" : { "type" : "AddressInfoType" },
          "Email" : { "type" : "EmailType" },
          "URL" : { "type" : "URL_Type" },
          "CompanyName" : { "type" : "CompanyNameType" },
          "EmployeeInfo" : { "type" : "EmployeeInfoType" },
          "ShareSynchInd" : { "type" : "anonymous201" },
          "ShareMarketInd" : { "type" : "anonymous202" },
          "DefaultInd" : { "type" : "boolean" },
          "ContactType" : { "type" : "text" },
          "Relation" : { "type" : "text" },
          "EmergencyFlag" : { "type" : "boolean" },
          "RPH" : { "type" : "text" }
        }
      },
      "EmployeeInfoType" : {
        "label" : "EmployeeInfoType",
        "property info" : {
          "_" : { "type" : "text" },
          "EmployeeId" : { "type" : "text" },
          "EmployeeLevel" : { "type" : "text" },
          "EmployeeTitle" : { "type" : "text" },
          "EmployeeStatus" : { "type" : "text" }
        }
      },
      "DocumentType" : {
        "label" : "DocumentType",
        "property info" : {
          "DocHolderFormattedName" : { "type" : "PersonNameType" },
          "DocHolderName" : { "type" : "text" },
          "DocLimitations" : { "type" : "text" },
          "AdditionalPersonNames" : { "type" : "list\\u003Cstring\\u003E" },
          "ShareSynchInd" : { "type" : "anonymous205" },
          "ShareMarketInd" : { "type" : "anonymous206" },
          "DocIssueAuthority" : { "type" : "text" },
          "DocIssueLocation" : { "type" : "text" },
          "DocID" : { "type" : "text" },
          "DocType" : { "type" : "text" },
          "Gender" : { "type" : "anonymous207" },
          "BirthDate" : { "type" : "date" },
          "EffectiveDate" : { "type" : "date" },
          "ExpireDate" : { "type" : "date" },
          "DocIssueStateProv" : { "type" : "text" },
          "DocIssueCountry" : { "type" : "text" },
          "BirthCountry" : { "type" : "text" },
          "DocHolderNationality" : { "type" : "text" }
        }
      },
      "ArrayOfString" : {
        "label" : "ArrayOfString",
        "property info" : { "AdditionalPersonName" : { "type" : "text" } }
      },
      "PreferencesType" : {
        "label" : "PreferencesType",
        "property info" : {
          "PrefCollection" : { "type" : "PrefCollection" },
          "ShareSynchInd" : { "type" : "anonymous213" },
          "ShareMarketInd" : { "type" : "anonymous214" }
        }
      },
      "PrefCollection" : {
        "label" : "PrefCollection",
        "property info" : {
          "CommonPref" : { "type" : "CommonPrefType" },
          "VehicleRentalPref" : { "type" : "VehicleProfileRentalPrefType" },
          "AirlinePref" : { "type" : "AirlinePrefType" },
          "HotelPref" : { "type" : "HotelPrefType" },
          "OtherSrvcPref" : { "type" : "OtherSrvcPrefType" },
          "TPA_Extensions" : { "type" : "TPA_Extensions_Type" },
          "ShareSynchInd" : { "type" : "anonymous211" },
          "ShareMarketInd" : { "type" : "anonymous212" },
          "TravelPurpose" : { "type" : "text" }
        }
      },
      "CommonPrefType" : {
        "label" : "CommonPrefType",
        "property info" : {
          "NamePref" : { "type" : "NamePrefType" },
          "PhonePref" : { "type" : "PhonePrefType" },
          "AddressPref" : { "type" : "AddressPrefType" },
          "PaymentFormPref" : { "type" : "PaymentFormPrefType" },
          "InterestPref" : { "type" : "InterestPrefType" },
          "InsurancePref" : { "type" : "InsurancePrefType" },
          "SeatingPref" : { "type" : "SeatingPrefType" },
          "TicketDistribPref" : { "type" : "TicketDistribPrefType" },
          "MediaEntertainPref" : { "type" : "MediaEntertainPrefType" },
          "PetInfoPref" : { "type" : "PetInfoPrefType" },
          "MealPref" : { "type" : "MealPrefType" },
          "LoyaltyPref" : { "type" : "LoyaltyPrefType" },
          "SpecRequestPref" : { "type" : "SpecRequestPrefType" },
          "RelatedTravelerPref" : { "type" : "RelatedTravelerPrefType" },
          "TPA_Extensions" : { "type" : "TPA_Extensions_Type" },
          "ShareSynchInd" : { "type" : "anonymous216" },
          "ShareMarketInd" : { "type" : "anonymous217" },
          "SmokingAllowed" : { "type" : "boolean" },
          "PrimaryLangID" : { "type" : "language" },
          "AltLangID" : { "type" : "language" }
        }
      },
      "NamePrefType" : {
        "label" : "NamePrefType",
        "property info" : {
          "UniqueID" : { "type" : "UniqueID_Type" },
          "PersonName" : { "type" : "PersonNameType" },
          "PreferLevel" : { "type" : "PreferLevelType" }
        }
      },
      "PhonePrefType" : {
        "label" : "PhonePrefType",
        "property info" : { "Telephone" : { "type" : "Telephone" } }
      },
      "AddressPrefType" : {
        "label" : "AddressPrefType",
        "property info" : {
          "Address" : { "type" : "AddressInfoType" },
          "ShareSynchInd" : { "type" : "anonymous224" },
          "ShareMarketInd" : { "type" : "anonymous225" }
        }
      },
      "PaymentFormPrefType" : {
        "label" : "PaymentFormPrefType",
        "property info" : {
          "_" : { "type" : "text" },
          "PreferLevel" : { "type" : "PreferLevelType" },
          "RPH" : { "type" : "text" }
        }
      },
      "InterestPrefType" : {
        "label" : "InterestPrefType",
        "property info" : {
          "_" : { "type" : "text" },
          "PreferLevel" : { "type" : "PreferLevelType" }
        }
      },
      "InsurancePrefType" : {
        "label" : "InsurancePrefType",
        "property info" : {
          "_" : { "type" : "text" },
          "PreferLevel" : { "type" : "PreferLevelType" },
          "RPH" : { "type" : "text" }
        }
      },
      "SeatingPrefType" : {
        "label" : "SeatingPrefType",
        "property info" : {
          "_" : { "type" : "text" },
          "PreferLevel" : { "type" : "PreferLevelType" },
          "SeatDirection" : { "type" : "text" },
          "SeatLocation" : { "type" : "text" },
          "SeatPosition" : { "type" : "text" },
          "SeatRow" : { "type" : "text" }
        }
      },
      "TicketDistribPrefType" : {
        "label" : "TicketDistribPrefType",
        "property info" : {
          "_" : { "type" : "text" },
          "PreferLevel" : { "type" : "PreferLevelType" },
          "DistribType" : { "type" : "text" },
          "TicketTime" : { "type" : "duration" }
        }
      },
      "MediaEntertainPrefType" : {
        "label" : "MediaEntertainPrefType",
        "property info" : {
          "_" : { "type" : "text" },
          "PreferLevel" : { "type" : "PreferLevelType" }
        }
      },
      "PetInfoPrefType" : {
        "label" : "PetInfoPrefType",
        "property info" : {
          "_" : { "type" : "text" },
          "PreferLevel" : { "type" : "PreferLevelType" }
        }
      },
      "MealPrefType" : {
        "label" : "MealPrefType",
        "property info" : {
          "_" : { "type" : "text" },
          "PreferLevel" : { "type" : "PreferLevelType" },
          "MealType" : { "type" : "MealType" },
          "FavoriteFood" : { "type" : "text" },
          "Beverage" : { "type" : "text" }
        }
      },
      "LoyaltyPrefType" : {
        "label" : "LoyaltyPrefType",
        "property info" : {
          "_" : { "type" : "text" },
          "PreferLevel" : { "type" : "PreferLevelType" },
          "RPH" : { "type" : "text" }
        }
      },
      "SpecRequestPrefType" : {
        "label" : "SpecRequestPrefType",
        "property info" : {
          "_" : { "type" : "text" },
          "PreferLevel" : { "type" : "PreferLevelType" }
        }
      },
      "RelatedTravelerPrefType" : {
        "label" : "RelatedTravelerPrefType",
        "property info" : {
          "UniqueID" : { "type" : "UniqueID_Type" },
          "PreferLevel" : { "type" : "PreferLevelType" }
        }
      },
      "VehicleProfileRentalPrefType" : {
        "label" : "VehicleProfileRentalPrefType",
        "property info" : {
          "LoyaltyPref" : { "type" : "LoyaltyPref" },
          "VendorPref" : { "type" : "CompanyNamePrefType" },
          "PaymentFormPref" : { "type" : "PaymentFormPref" },
          "CoveragePref" : { "type" : "CoveragePref" },
          "SpecialReqPref" : { "type" : "VehicleSpecialReqPrefType" },
          "VehTypePref" : { "type" : "VehiclePrefType" },
          "SpecialEquipPref" : { "type" : "SpecialEquipPref" },
          "PreferLevel" : { "type" : "PreferLevelType" },
          "ShareSynchInd" : { "type" : "anonymous243" },
          "ShareMarketInd" : { "type" : "anonymous244" },
          "SmokingAllowed" : { "type" : "boolean" },
          "GasPrePay" : { "type" : "boolean" }
        }
      },
      "LoyaltyPref" : {
        "label" : "LoyaltyPref",
        "property info" : { "RPH" : { "type" : "text" } }
      },
      "PaymentFormPref" : {
        "label" : "PaymentFormPref",
        "property info" : { "RPH" : { "type" : "text" } }
      },
      "CoveragePref" : { "label" : "CoveragePref", "property info" : [] },
      "SpecialEquipPref" : {
        "label" : "SpecialEquipPref",
        "property info" : { "Action" : { "type" : "ActionType" } }
      },
      "VehicleSpecialReqPrefType" : {
        "label" : "VehicleSpecialReqPrefType",
        "property info" : {
          "_" : { "type" : "text" },
          "PreferLevel" : { "type" : "PreferLevelType" }
        }
      },
      "VehiclePrefType" : {
        "label" : "VehiclePrefType",
        "property info" : {
          "TypePref" : { "type" : "PreferLevelType" },
          "ClassPref" : { "type" : "PreferLevelType" },
          "AirConditionPref" : { "type" : "PreferLevelType" },
          "TransmissionPref" : { "type" : "PreferLevelType" },
          "VendorCarType" : { "type" : "text" },
          "VehicleQty" : { "type" : "nonNegativeInteger" },
          "Code" : { "type" : "text" },
          "CodeContext" : { "type" : "text" }
        }
      },
      "VehicleCoreType" : {
        "label" : "VehicleCoreType",
        "property info" : {
          "VehType" : { "type" : "VehType" },
          "VehClass" : { "type" : "VehClass" },
          "AirConditionInd" : { "type" : "boolean" },
          "TransmissionType" : { "type" : "VehicleTransmissionType" },
          "FuelType" : { "type" : "anonymous250" },
          "DriveType" : { "type" : "anonymous251" }
        }
      },
      "VehType" : {
        "label" : "VehType",
        "property info" : {
          "VehicleCategory" : { "type" : "text" },
          "DoorCount" : { "type" : "text" }
        }
      },
      "VehClass" : {
        "label" : "VehClass",
        "property info" : { "Size" : { "type" : "text" } }
      },
      "AirlinePrefType" : {
        "label" : "AirlinePrefType",
        "property info" : {
          "LoyaltyPref" : { "type" : "LoyaltyPrefType" },
          "VendorPref" : { "type" : "CompanyNamePrefType" },
          "PaymentFormPref" : { "type" : "PaymentFormPrefType" },
          "AirportOriginPref" : { "type" : "AirportPrefType" },
          "AirportRoutePref" : { "type" : "AirportPrefType" },
          "FareRestrictPref" : { "type" : "FareRestrictPref" },
          "FlightTypePref" : { "type" : "FlightTypePref" },
          "EquipPref" : { "type" : "EquipmentTypePref" },
          "CabinPref" : { "type" : "CabinPref" },
          "SeatPref" : { "type" : "SeatPref" },
          "TicketDistribPref" : { "type" : "TicketDistribPrefType" },
          "MealPref" : { "type" : "MealPrefType" },
          "SpecRequestPref" : { "type" : "SpecRequestPrefType" },
          "SSR_Pref" : { "type" : "SSR_Pref" },
          "TPA_Extensions" : { "type" : "TPA_Extensions_Type" },
          "MediaEntertainPref" : { "type" : "MediaEntertainPrefType" },
          "PetInfoPref" : { "type" : "PetInfoPrefType" },
          "ShareSynchInd" : { "type" : "anonymous262" },
          "ShareMarketInd" : { "type" : "anonymous263" },
          "PreferLevel" : { "type" : "PreferLevelType" },
          "SmokingAllowed" : { "type" : "boolean" },
          "PassengerTypeCode" : { "type" : "text" },
          "AirTicketType" : { "type" : "TicketType" }
        }
      },
      "FareRestrictPref" : {
        "label" : "FareRestrictPref",
        "property info" : { "FareRestriction" : { "type" : "text" }, "Date" : { "type" : "text" } }
      },
      "FlightTypePref" : {
        "label" : "FlightTypePref",
        "property info" : {
          "FlightType" : { "type" : "FlightTypeType" },
          "MaxConnections" : { "type" : "nonNegativeInteger" },
          "NonScheduledFltInfo" : { "type" : "anonymous257" },
          "BackhaulIndicator" : { "type" : "boolean" },
          "GroundTransportIndicator" : { "type" : "boolean" },
          "DirectAndNonStopOnlyInd" : { "type" : "boolean" },
          "NonStopsOnlyInd" : { "type" : "boolean" },
          "OnlineConnectionsOnlyInd" : { "type" : "boolean" },
          "RoutingType" : { "type" : "anonymous258" }
        }
      },
      "CabinPref" : {
        "label" : "CabinPref",
        "property info" : { "Cabin" : { "type" : "CabinType" } }
      },
      "SeatPref" : { "label" : "SeatPref", "property info" : [] },
      "SSR_Pref" : {
        "label" : "SSR_Pref",
        "property info" : { "SSR_Code" : { "type" : "text" } }
      },
      "AirportPrefType" : {
        "label" : "AirportPrefType",
        "property info" : {
          "_" : { "type" : "LocationType" },
          "PreferLevel" : { "type" : "PreferLevelType" }
        }
      },
      "LocationType" : {
        "label" : "LocationType",
        "property info" : {
          "_" : { "type" : "text" },
          "LocationCode" : { "type" : "text" },
          "CodeContext" : { "type" : "text" }
        }
      },
      "EquipmentTypePref" : {
        "label" : "EquipmentTypePref",
        "property info" : {
          "_" : { "type" : "EquipmentType" },
          "PreferLevel" : { "type" : "PreferLevelType" },
          "WideBody" : { "type" : "boolean" }
        }
      },
      "EquipmentType" : {
        "label" : "EquipmentType",
        "property info" : {
          "_" : { "type" : "text" },
          "AirEquipType" : { "type" : "text" },
          "ChangeofGauge" : { "type" : "boolean" }
        }
      },
      "HotelPrefType" : {
        "label" : "HotelPrefType",
        "property info" : {
          "LoyaltyPref" : { "type" : "LoyaltyPrefType" },
          "PaymentFormPref" : { "type" : "PaymentFormPrefType" },
          "HotelChainPref" : { "type" : "CompanyNamePrefType" },
          "PropertyNamePref" : { "type" : "PropertyNamePrefType" },
          "PropertyLocationPref" : { "type" : "PropertyLocationPrefType" },
          "PropertyTypePref" : { "type" : "PropertyTypePrefType" },
          "PropertyClassPref" : { "type" : "PropertyClassPrefType" },
          "PropertyAmenityPref" : { "type" : "PropertyAmenityPrefType" },
          "RoomAmenityPref" : { "type" : "RoomAmenityPrefType" },
          "RoomLocationPref" : { "type" : "RoomLocationPrefType" },
          "BedTypePref" : { "type" : "BedTypePrefType" },
          "FoodSrvcPref" : { "type" : "FoodSrvcPrefType" },
          "MediaEntertainPref" : { "type" : "MediaEntertainPrefType" },
          "PetInfoPref" : { "type" : "PetInfoPrefType" },
          "MealPref" : { "type" : "MealPrefType" },
          "RecreationSrvcPref" : { "type" : "RecreationSrvcPrefType" },
          "BusinessSrvcPref" : { "type" : "BusinessSrvcPrefType" },
          "PersonalSrvcPref" : { "type" : "PersonalSrvcPrefType" },
          "SecurityFeaturePref" : { "type" : "SecurityFeaturePrefType" },
          "PhysChallFeaturePref" : { "type" : "PhysChallFeaturePrefType" },
          "SpecRequestPref" : { "type" : "SpecRequestPrefType" },
          "TPA_Extensions" : { "type" : "TPA_Extensions_Type" },
          "PreferLevel" : { "type" : "PreferLevelType" },
          "ShareSynchInd" : { "type" : "anonymous272" },
          "ShareMarketInd" : { "type" : "anonymous273" },
          "SmokingAllowed" : { "type" : "boolean" },
          "RatePlanCode" : { "type" : "text" },
          "HotelGuestType" : { "type" : "text" }
        }
      },
      "PropertyNamePrefType" : {
        "label" : "PropertyNamePrefType",
        "property info" : {
          "_" : { "type" : "text" },
          "PreferLevel" : { "type" : "PreferLevelType" }
        }
      },
      "PropertyLocationPrefType" : {
        "label" : "PropertyLocationPrefType",
        "property info" : {
          "_" : { "type" : "text" },
          "PreferLevel" : { "type" : "PreferLevelType" },
          "PropertyLocationType" : { "type" : "text" }
        }
      },
      "PropertyTypePrefType" : {
        "label" : "PropertyTypePrefType",
        "property info" : {
          "_" : { "type" : "text" },
          "PreferLevel" : { "type" : "PreferLevelType" },
          "PropertyType" : { "type" : "text" }
        }
      },
      "PropertyClassPrefType" : {
        "label" : "PropertyClassPrefType",
        "property info" : {
          "_" : { "type" : "text" },
          "PreferLevel" : { "type" : "PreferLevelType" },
          "PropertyClassType" : { "type" : "text" }
        }
      },
      "PropertyAmenityPrefType" : {
        "label" : "PropertyAmenityPrefType",
        "property info" : {
          "_" : { "type" : "text" },
          "PreferLevel" : { "type" : "PreferLevelType" },
          "PropertyAmenityType" : { "type" : "text" }
        }
      },
      "RoomAmenityPrefType" : {
        "label" : "RoomAmenityPrefType",
        "property info" : {
          "_" : { "type" : "text" },
          "PreferLevel" : { "type" : "PreferLevelType" },
          "RoomAmenity" : { "type" : "text" },
          "ExistsCode" : { "type" : "text" },
          "Quantity" : { "type" : "nonNegativeInteger" },
          "QualityLevel" : { "type" : "text" }
        }
      },
      "RoomLocationPrefType" : {
        "label" : "RoomLocationPrefType",
        "property info" : {
          "_" : { "type" : "text" },
          "PreferLevel" : { "type" : "PreferLevelType" },
          "RoomLocationType" : { "type" : "text" }
        }
      },
      "BedTypePrefType" : {
        "label" : "BedTypePrefType",
        "property info" : {
          "_" : { "type" : "text" },
          "PreferLevel" : { "type" : "PreferLevelType" },
          "BedType" : { "type" : "text" }
        }
      },
      "FoodSrvcPrefType" : {
        "label" : "FoodSrvcPrefType",
        "property info" : {
          "_" : { "type" : "text" },
          "PreferLevel" : { "type" : "PreferLevelType" },
          "FoodSrvcType" : { "type" : "text" }
        }
      },
      "RecreationSrvcPrefType" : {
        "label" : "RecreationSrvcPrefType",
        "property info" : {
          "_" : { "type" : "text" },
          "PreferLevel" : { "type" : "PreferLevelType" },
          "RecreationSrvcType" : { "type" : "text" }
        }
      },
      "BusinessSrvcPrefType" : {
        "label" : "BusinessSrvcPrefType",
        "property info" : {
          "_" : { "type" : "text" },
          "PreferLevel" : { "type" : "PreferLevelType" },
          "BusinessSrvcType" : { "type" : "text" }
        }
      },
      "PersonalSrvcPrefType" : {
        "label" : "PersonalSrvcPrefType",
        "property info" : {
          "_" : { "type" : "text" },
          "PreferLevel" : { "type" : "PreferLevelType" }
        }
      },
      "SecurityFeaturePrefType" : {
        "label" : "SecurityFeaturePrefType",
        "property info" : {
          "_" : { "type" : "text" },
          "PreferLevel" : { "type" : "PreferLevelType" }
        }
      },
      "PhysChallFeaturePrefType" : {
        "label" : "PhysChallFeaturePrefType",
        "property info" : {
          "_" : { "type" : "text" },
          "PreferLevel" : { "type" : "PreferLevelType" },
          "PhysChallFeatureType" : { "type" : "text" }
        }
      },
      "OtherSrvcPrefType" : {
        "label" : "OtherSrvcPrefType",
        "property info" : {
          "OtherSrvcName" : { "type" : "text" },
          "VendorPref" : { "type" : "CompanyNamePrefType" },
          "LoyaltyPref" : { "type" : "LoyaltyPrefType" },
          "PaymentFormPref" : { "type" : "PaymentFormPrefType" },
          "SpecRequestPref" : { "type" : "SpecRequestPrefType" },
          "TPA_Extensions" : { "type" : "TPA_Extensions_Type" },
          "PreferLevel" : { "type" : "PreferLevelType" },
          "ShareSynchInd" : { "type" : "anonymous289" },
          "ShareMarketInd" : { "type" : "anonymous290" },
          "TravelPurpose" : { "type" : "text" }
        }
      },
      "CompanyInfoType" : {
        "label" : "CompanyInfoType",
        "property info" : {
          "CompanyName" : { "type" : "CompanyNameType" },
          "AddressInfo" : { "type" : "AddressInfoType" },
          "TelephoneInfo" : { "type" : "TelephoneInfoType" },
          "Email" : { "type" : "EmailType" },
          "URL" : { "type" : "URL_Type" },
          "BusinessLocale" : { "type" : "AddressType" },
          "PaymentForm" : { "type" : "PaymentFormType" },
          "ContactPerson" : { "type" : "ContactPersonType" },
          "TravelArranger" : { "type" : "TravelArrangerType" },
          "LoyaltyProgram" : { "type" : "LoyaltyProgramType" }
        }
      },
      "TelephoneInfoType" : {
        "label" : "TelephoneInfoType",
        "property info" : {
          "ShareSynchInd" : { "type" : "anonymous293" },
          "ShareMarketInd" : { "type" : "anonymous294" },
          "PhoneLocationType" : { "type" : "text" },
          "PhoneTechType" : { "type" : "text" },
          "PhoneUseType" : { "type" : "text" },
          "CountryAccessCode" : { "type" : "text" },
          "AreaCityCode" : { "type" : "text" },
          "PhoneNumber" : { "type" : "text" },
          "Extension" : { "type" : "text" },
          "PIN" : { "type" : "text" },
          "FormattedInd" : { "type" : "boolean" },
          "DefaultInd" : { "type" : "boolean" },
          "RPH" : { "type" : "text" }
        }
      },
      "LoyaltyProgramType" : {
        "label" : "LoyaltyProgramType",
        "property info" : {
          "_" : { "type" : "text" },
          "ProgramCode" : { "type" : "text" },
          "SingleVendorInd" : { "type" : "anonymous296" },
          "LoyaltyLevel" : { "type" : "text" },
          "RPH" : { "type" : "text" }
        }
      },
      "AffiliationsType" : {
        "label" : "AffiliationsType",
        "property info" : {
          "Organization" : { "type" : "OrganizationType" },
          "Employer" : { "type" : "EmployerType" },
          "TravelArranger" : { "type" : "TravelArrangerType" },
          "TravelClub" : { "type" : "TravelClubType" },
          "Insurance" : { "type" : "InsuranceType" },
          "TPA_Extensions" : { "type" : "TPA_Extensions_Type" },
          "ShareSynchInd" : { "type" : "anonymous298" },
          "ShareMarketInd" : { "type" : "anonymous299" }
        }
      },
      "OrganizationType" : {
        "label" : "OrganizationType",
        "property info" : {
          "OrgMemberName" : { "type" : "OrgMemberName" },
          "OrgName" : { "type" : "CompanyNameType" },
          "RelatedOrgName" : { "type" : "CompanyNameType" },
          "TravelArranger" : { "type" : "TravelArrangerType" },
          "DefaultInd" : { "type" : "boolean" },
          "ShareSynchInd" : { "type" : "anonymous302" },
          "ShareMarketInd" : { "type" : "anonymous303" },
          "EffectiveDate" : { "type" : "date" },
          "ExpireDate" : { "type" : "date" },
          "OfficeType" : { "type" : "OfficeLocationType" }
        }
      },
      "OrgMemberName" : {
        "label" : "OrgMemberName",
        "property info" : { "Level" : { "type" : "text" }, "Title" : { "type" : "text" } }
      },
      "EmployerType" : {
        "label" : "EmployerType",
        "property info" : {
          "CompanyName" : { "type" : "CompanyNameType" },
          "RelatedEmployer" : { "type" : "CompanyNameType" },
          "EmployeeInfo" : { "type" : "EmployeeInfoType" },
          "InternalRefNmbr" : { "type" : "FreeTextType" },
          "TravelArranger" : { "type" : "TravelArrangerType" },
          "LoyaltyProgram" : { "type" : "LoyaltyProgramType" },
          "DefaultInd" : { "type" : "boolean" },
          "OfficeType" : { "type" : "OfficeLocationType" },
          "EffectiveDate" : { "type" : "date" },
          "ExpireDate" : { "type" : "date" }
        }
      },
      "TravelClubType" : {
        "label" : "TravelClubType",
        "property info" : {
          "TravelClubName" : { "type" : "CompanyNameType" },
          "ClubMemberName" : { "type" : "ClubMemberName" },
          "ShareSynchInd" : { "type" : "anonymous308" },
          "ShareMarketInd" : { "type" : "anonymous309" },
          "EffectiveDate" : { "type" : "date" },
          "ExpireDate" : { "type" : "date" }
        }
      },
      "ClubMemberName" : {
        "label" : "ClubMemberName",
        "property info" : { "ID" : { "type" : "text" } }
      },
      "InsuranceType" : {
        "label" : "InsuranceType",
        "property info" : {
          "InsuredName" : { "type" : "PersonNameType" },
          "InsuranceCompany" : { "type" : "CompanyNameType" },
          "Underwriter" : { "type" : "CompanyNameType" },
          "ShareSynchInd" : { "type" : "anonymous311" },
          "ShareMarketInd" : { "type" : "anonymous312" },
          "InsuranceType" : { "type" : "text" },
          "PolicyNumber" : { "type" : "text" },
          "EffectiveDate" : { "type" : "date" },
          "ExpireDate" : { "type" : "date" },
          "RPH" : { "type" : "text" }
        }
      },
      "AgreementsType" : {
        "label" : "AgreementsType",
        "property info" : {
          "Certification" : { "type" : "CertificationType" },
          "AllianceConsortium" : { "type" : "AllianceConsortiumType" },
          "CommissionInfo" : { "type" : "CommissionInfoType" },
          "TPA_Extensions" : { "type" : "TPA_Extensions_Type" },
          "ShareSynchInd" : { "type" : "anonymous314" },
          "ShareMarketInd" : { "type" : "anonymous315" }
        }
      },
      "AllianceConsortiumType" : {
        "label" : "AllianceConsortiumType",
        "property info" : {
          "AllianceMember" : { "type" : "AllianceMember" },
          "ID" : { "type" : "text" },
          "EffectiveDate" : { "type" : "date" },
          "ExpireDate" : { "type" : "date" }
        }
      },
      "AllianceMember" : {
        "label" : "AllianceMember",
        "property info" : {
          "_" : { "type" : "CompanyNameType" },
          "MemberCode" : { "type" : "text" }
        }
      },
      "PropertyManagerType" : {
        "label" : "PropertyManagerType",
        "property info" : {
          "PropertyManagerCode" : { "type" : "text" },
          "CurrencyCode" : { "type" : "text" },
          "DecimalPlaces" : { "type" : "nonNegativeInteger" }
        }
      },
      "EVRN_ResGlobalInfoType" : {
        "label" : "EVRN_ResGlobalInfoType",
        "property info" : {
          "UnitReservationIDs" : { "type" : "list\\u003CUnitReservationIDsTypeUnitReservationID\\u003E" },
          "RoutingHops" : { "type" : "list\\u003CRoutingHopTypeRoutingHop\\u003E" },
          "Profiles" : { "type" : "list\\u003CProfilesTypeProfileInfo\\u003E" }
        }
      },
      "ArrayOfUnitReservationIDsTypeUnitReservationID" : {
        "label" : "ArrayOfUnitReservationIDsTypeUnitReservationID",
        "property info" : { "UnitReservationID" : { "type" : "UnitReservationID" } }
      },
      "UnitReservationID" : {
        "label" : "UnitReservationID",
        "property info" : {
          "ResID_Type" : { "type" : "text" },
          "ResID_Value" : { "type" : "text" },
          "ResID_Source" : { "type" : "text" },
          "ResID_SourceContext" : { "type" : "text" },
          "ResID_Date" : { "type" : "dateTime" },
          "ForGuest" : { "type" : "boolean" },
          "ResGuestRPH" : { "type" : "text" },
          "CancelOriginatorCode" : { "type" : "text" },
          "CancellationDate" : { "type" : "dateTime" }
        }
      },
      "ArrayOfResGuestsTypeResGuest" : {
        "label" : "ArrayOfResGuestsTypeResGuest",
        "property info" : { "ResGuest" : { "type" : "ResGuest" } }
      },
      "ResGuest" : {
        "label" : "ResGuest",
        "property info" : {
          "Profiles" : { "type" : "list\\u003CProfilesTypeProfileInfo\\u003E" },
          "SpecialRequests" : { "type" : "list\\u003CSpecialRequestTypeSpecialRequest\\u003E" },
          "Comments" : { "type" : "list\\u003CCommentTypeComment\\u003E" },
          "ServiceRPHs" : { "type" : "list\\u003CServiceRPHsTypeServiceRPH\\u003E" },
          "ProfileRPHs" : { "type" : "list\\u003CResGuestsTypeResGuestProfileRPH\\u003E" },
          "ArrivalTransport" : { "type" : "TransportInfoType" },
          "DepartureTransport" : { "type" : "TransportInfoType" },
          "GuestCounts" : { "type" : "GuestCountType" },
          "InHouseTimeSpan" : { "type" : "DateTimeSpanType" },
          "TPA_Extensions" : { "type" : "TPA_Extensions_Type" },
          "ResGuestRPH" : { "type" : "text" },
          "AgeQualifyingCode" : { "type" : "text" },
          "ArrivalTime" : { "type" : "time" },
          "DepartureTime" : { "type" : "time" },
          "GroupEventCode" : { "type" : "text" },
          "VIP" : { "type" : "boolean" }
        }
      },
      "ArrayOfResGuestsTypeResGuestProfileRPH" : {
        "label" : "ArrayOfResGuestsTypeResGuestProfileRPH",
        "property info" : { "ProfileRPH" : { "type" : "ProfileRPH" } }
      },
      "ProfileRPH" : {
        "label" : "ProfileRPH",
        "property info" : { "RPH" : { "type" : "text" } }
      },
      "TransportInfoType" : {
        "label" : "TransportInfoType",
        "property info" : { "TransportInfo" : { "type" : "TransportInfo" } }
      },
      "TransportInfo" : {
        "label" : "TransportInfo",
        "property info" : {
          "Type" : { "type" : "text" },
          "ID" : { "type" : "text" },
          "LocationCode" : { "type" : "text" },
          "Time" : { "type" : "dateTime" }
        }
      },
      "WrittenConfInstType" : {
        "label" : "WrittenConfInstType",
        "property info" : {
          "SupplementalData" : { "type" : "ParagraphType" },
          "Email" : { "type" : "EmailType" },
          "LanguageID" : { "type" : "text" },
          "AddresseeName" : { "type" : "text" },
          "Address" : { "type" : "text" },
          "Telephone" : { "type" : "text" },
          "ConfirmInd" : { "type" : "boolean" }
        }
      },
      "ArrayOfUnitDescriptiveInfoRequestType" : {
        "label" : "ArrayOfUnitDescriptiveInfoRequestType",
        "property info" : { "UnitDescriptiveInfo" : { "type" : "UnitDescriptiveInfoRequestType" } }
      },
      "UnitDescriptiveInfoRequestType" : {
        "label" : "UnitDescriptiveInfoRequestType",
        "property info" : {
          "UnitInfo" : { "type" : "UnitInfo" },
          "Policies" : { "type" : "Policies" },
          "UnitReviews" : { "type" : "UnitReviews" },
          "Promotions" : { "type" : "Promotions" },
          "PropertyManagerCode" : { "type" : "text" },
          "UnitCode" : { "type" : "text" },
          "UnitName" : { "type" : "text" },
          "InfoSource" : { "type" : "text" },
          "InternalUnitCode" : { "type" : "text" },
          "UnitHeadline" : { "type" : "text" },
          "PropertyURL" : { "type" : "text" },
          "StateCodeList" : { "type" : "anonymous339" },
          "CountryCodeList" : { "type" : "anonymous340" },
          "BrandCodeList" : { "type" : "anonymous341" },
          "MoreDataEchoToken" : { "type" : "text" },
          "UpdatedAfter" : { "type" : "dateTime" }
        }
      },
      "UnitInfo" : {
        "label" : "UnitInfo",
        "property info" : { "SendData" : { "type" : "boolean" } }
      },
      "Policies" : {
        "label" : "Policies",
        "property info" : { "SendPolicies" : { "type" : "boolean" } }
      },
      "UnitReviews" : {
        "label" : "UnitReviews",
        "property info" : { "SendReviews" : { "type" : "boolean" } }
      },
      "Promotions" : {
        "label" : "Promotions",
        "property info" : { "SendPromotions" : { "type" : "boolean" } }
      },
      "EVRN_UnitDescriptiveInfoRS" : {
        "label" : "EVRN_UnitDescriptiveInfoRS",
        "property info" : {
          "Warnings" : { "type" : "WarningsType" },
          "Errors" : { "type" : "ErrorsType" },
          "UnitDescriptiveContents" : { "type" : "UnitDescriptiveContents" },
          "Success" : { "type" : "SuccessType" }
        }
      },
      "UnitDescriptiveContents" : {
        "label" : "UnitDescriptiveContents",
        "property info" : {
          "UnitDescriptiveContent" : { "type" : "UnitDescriptiveContentType" },
          "CachedData" : { "type" : "boolean" }
        }
      },
      "EVRN_BaseRSType" : {
        "label" : "EVRN_BaseRSType",
        "property info" : {
          "EchoToken" : { "type" : "text" },
          "TimeStamp" : { "type" : "dateTime" },
          "Target" : { "type" : "anonymous345" },
          "Version" : { "type" : "decimal" },
          "TransactionIdentifier" : { "type" : "text" },
          "SequenceNmbr" : { "type" : "nonNegativeInteger" },
          "TransactionStatusCode" : { "type" : "anonymous346" },
          "RetransmissionIndicator" : { "type" : "boolean" }
        }
      },
      "EVRN_UnitCalendarAvailBatchRSType" : {
        "label" : "EVRN_UnitCalendarAvailBatchRSType",
        "property info" : {
          "Warnings" : { "type" : "WarningsType" },
          "Errors" : { "type" : "ErrorsType" },
          "UnitCalendarAvails" : { "type" : "UnitCalendarAvails" },
          "Success" : { "type" : "SuccessType" }
        }
      },
      "UnitCalendarAvails" : {
        "label" : "UnitCalendarAvails",
        "property info" : {
          "UnitCalendarAvail" : { "type" : "UnitCalendarAvailType" },
          "CachedData" : { "type" : "boolean" }
        }
      },
      "WarningsType" : {
        "label" : "WarningsType",
        "property info" : { "Warning" : { "type" : "WarningType" } }
      },
      "ErrorsType" : {
        "label" : "ErrorsType",
        "property info" : { "Error" : { "type" : "ErrorType" } }
      },
      "UnitCalendarAvailType" : {
        "label" : "UnitCalendarAvailType",
        "property info" : {
          "UnitCalendarAvailSegment" : { "type" : "UnitCalendarAvailSegmentType" },
          "PropertyManagerCode" : { "type" : "text" },
          "UnitCode" : { "type" : "text" },
          "UnitName" : { "type" : "text" },
          "InfoSource" : { "type" : "text" },
          "InternalUnitCode" : { "type" : "text" },
          "UnitHeadline" : { "type" : "text" },
          "PropertyURL" : { "type" : "text" },
          "LastUpdated" : { "type" : "dateTime" }
        }
      },
      "UnitCalendarAvailSegmentType" : {
        "label" : "UnitCalendarAvailSegmentType",
        "property info" : {
          "DailyAvailability" : { "type" : "text" },
          "StayRequirements" : { "type" : "list\\u003CStayRequirementType\\u003E" },
          "StartDate" : { "type" : "date" },
          "EndDate" : { "type" : "date" }
        }
      },
      "ArrayOfStayRequirementType" : {
        "label" : "ArrayOfStayRequirementType",
        "property info" : { "StayRequirement" : { "type" : "StayRequirementType" } }
      },
      "StayRequirementType" : {
        "label" : "StayRequirementType",
        "property info" : {
          "Description" : { "type" : "ParagraphType" },
          "Mon" : { "type" : "boolean" },
          "Tue" : { "type" : "boolean" },
          "Weds" : { "type" : "boolean" },
          "Thur" : { "type" : "boolean" },
          "Fri" : { "type" : "boolean" },
          "Sat" : { "type" : "boolean" },
          "Sun" : { "type" : "boolean" },
          "MinLOS" : { "type" : "nonNegativeInteger" },
          "MaxLOS" : { "type" : "nonNegativeInteger" },
          "StayContext" : { "type" : "anonymous355" }
        }
      },
      "SuccessType" : { "label" : "SuccessType", "property info" : [] },
      "UnitResResponseType" : {
        "label" : "UnitResResponseType",
        "property info" : {
          "POS" : { "type" : "list\\u003CSourceType\\u003E" },
          "Warnings" : { "type" : "WarningsType" },
          "UnitReservations" : { "type" : "UnitReservationsType" },
          "Errors" : { "type" : "ErrorsType" },
          "Success" : { "type" : "SuccessType" },
          "ResResponseType" : { "type" : "TransactionStatusType" }
        }
      },
      "UnitDescriptiveContentType" : {
        "label" : "UnitDescriptiveContentType",
        "property info" : {
          "UnitInfo" : { "type" : "UnitInfoType" },
          "Policies" : { "type" : "list\\u003CEVRN_PoliciesTypePolicy\\u003E" },
          "UnitReviews" : { "type" : "UnitReviewsType" },
          "Promotions" : { "type" : "PromotionsType" },
          "PropertyManagerCode" : { "type" : "text" },
          "UnitCode" : { "type" : "text" },
          "UnitName" : { "type" : "text" },
          "InfoSource" : { "type" : "text" },
          "InternalUnitCode" : { "type" : "text" },
          "UnitHeadline" : { "type" : "text" },
          "PropertyURL" : { "type" : "text" }
        }
      },
      "UnitInfoType" : {
        "label" : "UnitInfoType",
        "property info" : {
          "UnitName" : { "type" : "UnitName" },
          "CategoryCodes" : { "type" : "EVRN_CategoryCodesType" },
          "Descriptions" : { "type" : "Descriptions" },
          "Position" : { "type" : "Position" },
          "Services" : { "type" : "list\\u003CUnitInfoTypeService\\u003E" },
          "Address" : { "type" : "AddressType" },
          "UnitAmenity" : { "type" : "UnitAmenityType" },
          "RateRanges" : { "type" : "list\\u003CRateRangeType\\u003E" },
          "AreaSquareFeet" : { "type" : "decimal" },
          "MaxOccupancy" : { "type" : "nonNegativeInteger" },
          "NumberFloors" : { "type" : "nonNegativeInteger" },
          "WhenBuilt" : { "type" : "text" },
          "LastUpdated" : { "type" : "dateTime" }
        }
      },
      "UnitName" : {
        "label" : "UnitName",
        "property info" : { "_" : { "type" : "text" }, "UnitShortName" : { "type" : "text" } }
      },
      "Descriptions" : {
        "label" : "Descriptions",
        "property info" : {
          "MultimediaDescriptions" : { "type" : "MultimediaDescriptions" },
          "DescriptiveText" : { "type" : "text" },
          "RateNotes" : { "type" : "text" }
        }
      },
      "MultimediaDescriptions" : {
        "label" : "MultimediaDescriptions",
        "property info" : {
          "InfoCode" : { "type" : "text" },
          "AdditionalDetailCode" : { "type" : "text" }
        }
      },
      "EVRN_CategoryCodesType" : {
        "label" : "EVRN_CategoryCodesType",
        "property info" : {
          "LocationCategory" : { "type" : "LocationCategory" },
          "UnitCategory" : { "type" : "UnitCategory" },
          "RoomInfo" : { "type" : "RoomInfo" },
          "BedInfo" : { "type" : "BedInfo" },
          "PropertyManagerCategory" : { "type" : "PropertyManagerCategory" },
          "CustomCategoryGroup" : { "type" : "CustomCategoryGroupType" }
        }
      },
      "LocationCategory" : {
        "label" : "LocationCategory",
        "property info" : {
          "Code" : { "type" : "text" },
          "CodeDetail" : { "type" : "text" },
          "ExistsCode" : { "type" : "text" }
        }
      },
      "UnitCategory" : {
        "label" : "UnitCategory",
        "property info" : {
          "Code" : { "type" : "text" },
          "CodeDetail" : { "type" : "text" },
          "ExistsCode" : { "type" : "text" }
        }
      },
      "RoomInfo" : {
        "label" : "RoomInfo",
        "property info" : {
          "DescriptiveText" : { "type" : "text" },
          "Code" : { "type" : "text" },
          "CodeDetail" : { "type" : "text" },
          "Quantity" : { "type" : "decimal" }
        }
      },
      "BedInfo" : {
        "label" : "BedInfo",
        "property info" : {
          "Code" : { "type" : "text" },
          "CodeDetail" : { "type" : "text" },
          "Quantity" : { "type" : "nonNegativeInteger" }
        }
      },
      "PropertyManagerCategory" : {
        "label" : "PropertyManagerCategory",
        "property info" : { "Category" : { "type" : "text" }, "Option" : { "type" : "text" } }
      },
      "CustomCategoryGroupType" : {
        "label" : "CustomCategoryGroupType",
        "property info" : {
          "CustomCategory" : { "type" : "CustomCategoryType" },
          "Name" : { "type" : "text" }
        }
      },
      "CustomCategoryType" : {
        "label" : "CustomCategoryType",
        "property info" : { "Code" : { "type" : "text" }, "CodeDetail" : { "type" : "text" } }
      },
      "MultimediaDescriptionsType" : {
        "label" : "MultimediaDescriptionsType",
        "property info" : {
          "MultimediaDescription" : { "type" : "MultimediaDescriptionType" },
          "LastUpdated" : { "type" : "dateTime" }
        }
      },
      "MultimediaDescriptionType" : {
        "label" : "MultimediaDescriptionType",
        "property info" : {
          "ImageItems" : { "type" : "ImageItemsType" },
          "TextItems" : { "type" : "TextItemsType" },
          "VideoItems" : { "type" : "VideoItems" }
        }
      },
      "VideoItems" : {
        "label" : "VideoItems",
        "property info" : { "MoreData" : { "type" : "boolean" } }
      },
      "ImageItemsType" : {
        "label" : "ImageItemsType",
        "property info" : {
          "ImageItem" : { "type" : "ImageItem" },
          "MoreData" : { "type" : "boolean" }
        }
      },
      "ImageItem" : {
        "label" : "ImageItem",
        "property info" : {
          "CreateDateTime" : { "type" : "dateTime" },
          "CreatorID" : { "type" : "text" },
          "LastModifyDateTime" : { "type" : "dateTime" },
          "LastModifierID" : { "type" : "text" },
          "Removal" : { "type" : "boolean" },
          "Version" : { "type" : "text" },
          "IsDefault" : { "type" : "boolean" }
        }
      },
      "ImageDescriptionType" : {
        "label" : "ImageDescriptionType",
        "property info" : {
          "ImageFormat" : { "type" : "ImageFormat" },
          "Description" : { "type" : "Description" },
          "Category" : { "type" : "text" }
        }
      },
      "ImageFormat" : {
        "label" : "ImageFormat",
        "property info" : {
          "ContentID" : { "type" : "text" },
          "Title" : { "type" : "text" },
          "Author" : { "type" : "text" },
          "CopyrightNotice" : { "type" : "text" },
          "CopyrightOwner" : { "type" : "text" },
          "CopyrightStart" : { "type" : "text" },
          "CopyrightEnd" : { "type" : "text" },
          "EffectiveStart" : { "type" : "text" },
          "EffectiveEnd" : { "type" : "text" },
          "ApplicableStart" : { "type" : "text" },
          "ApplicableEnd" : { "type" : "text" },
          "RecordID" : { "type" : "text" },
          "Language" : { "type" : "language" },
          "Format" : { "type" : "text" },
          "FileName" : { "type" : "text" },
          "FileSize" : { "type" : "positiveInteger" },
          "DimensionCategory" : { "type" : "text" },
          "IsOriginalIndicator" : { "type" : "boolean" }
        }
      },
      "Description" : {
        "label" : "Description",
        "property info" : {
          "_" : { "type" : "FormattedTextTextType" },
          "ListItem" : { "type" : "integer" }
        }
      },
      "ImageItemType" : {
        "label" : "ImageItemType",
        "property info" : {
          "URL" : { "type" : "anyURI" },
          "UnitOfMeasureCode" : { "type" : "text" },
          "Width" : { "type" : "positiveInteger" },
          "Height" : { "type" : "positiveInteger" }
        }
      },
      "TextItemsType" : {
        "label" : "TextItemsType",
        "property info" : {
          "TextItem" : { "type" : "TextItem" },
          "MoreData" : { "type" : "boolean" }
        }
      },
      "TextItem" : {
        "label" : "TextItem",
        "property info" : {
          "CreateDateTime" : { "type" : "dateTime" },
          "CreatorID" : { "type" : "text" },
          "LastModifyDateTime" : { "type" : "dateTime" },
          "LastModifierID" : { "type" : "text" },
          "Removal" : { "type" : "boolean" },
          "Version" : { "type" : "text" }
        }
      },
      "TextDescriptionType" : {
        "label" : "TextDescriptionType",
        "property info" : {
          "URL" : { "type" : "anyURI" },
          "Description" : { "type" : "Description" },
          "Category" : { "type" : "text" },
          "ContentID" : { "type" : "text" },
          "Title" : { "type" : "text" },
          "Author" : { "type" : "text" },
          "CopyrightNotice" : { "type" : "text" },
          "CopyrightOwner" : { "type" : "text" },
          "CopyrightStart" : { "type" : "text" },
          "CopyrightEnd" : { "type" : "text" },
          "EffectiveStart" : { "type" : "text" },
          "EffectiveEnd" : { "type" : "text" },
          "ApplicableStart" : { "type" : "text" },
          "ApplicableEnd" : { "type" : "text" },
          "RecordID" : { "type" : "text" },
          "Language" : { "type" : "language" }
        }
      },
      "VideoItemsType" : {
        "label" : "VideoItemsType",
        "property info" : { "VideoItem" : { "type" : "VideoItem" } }
      },
      "VideoItem" : {
        "label" : "VideoItem",
        "property info" : {
          "Language" : { "type" : "language" },
          "Caption" : { "type" : "text" },
          "Removal" : { "type" : "boolean" },
          "Version" : { "type" : "text" },
          "CreateDateTime" : { "type" : "dateTime" },
          "CreatorID" : { "type" : "text" },
          "LastModifyDateTime" : { "type" : "dateTime" },
          "LastModifierID" : { "type" : "text" }
        }
      },
      "VideoDescriptionType" : {
        "label" : "VideoDescriptionType",
        "property info" : {
          "VideoFormat" : { "type" : "VideoFormat" },
          "Category" : { "type" : "text" }
        }
      },
      "VideoFormat" : {
        "label" : "VideoFormat",
        "property info" : {
          "ContentID" : { "type" : "text" },
          "Title" : { "type" : "text" },
          "Author" : { "type" : "text" },
          "CopyrightNotice" : { "type" : "text" },
          "CopyrightOwner" : { "type" : "text" },
          "CopyrightStart" : { "type" : "text" },
          "CopyrightEnd" : { "type" : "text" },
          "EffectiveStart" : { "type" : "text" },
          "EffectiveEnd" : { "type" : "text" },
          "ApplicableStart" : { "type" : "text" },
          "ApplicableEnd" : { "type" : "text" },
          "RecordID" : { "type" : "text" }
        }
      },
      "VideoItemType" : {
        "label" : "VideoItemType",
        "property info" : {
          "URL" : { "type" : "anyURI" },
          "UnitOfMeasureCode" : { "type" : "text" },
          "Width" : { "type" : "positiveInteger" },
          "Height" : { "type" : "positiveInteger" },
          "BitRate" : { "type" : "positiveInteger" },
          "Length" : { "type" : "positiveInteger" },
          "Language" : { "type" : "language" },
          "Format" : { "type" : "text" },
          "FileSize" : { "type" : "positiveInteger" },
          "FileName" : { "type" : "text" }
        }
      },
      "ArrayOfUnitInfoTypeService" : {
        "label" : "ArrayOfUnitInfoTypeService",
        "property info" : { "Service" : { "type" : "Service" } }
      },
      "DescriptiveText" : {
        "label" : "DescriptiveText",
        "property info" : { "_" : { "type" : "text" }, "Rel" : { "type" : "integer" } }
      },
      "RelativePositionType" : {
        "label" : "RelativePositionType",
        "property info" : {
          "Direction" : { "type" : "text" },
          "Distance" : { "type" : "text" },
          "DistanceUnitName" : { "type" : "DistanceUnitNameType" },
          "UnitOfMeasureCode" : { "type" : "text" },
          "Nearest" : { "type" : "boolean" },
          "IndexPointCode" : { "type" : "text" },
          "Name" : { "type" : "text" },
          "PrimaryIndicator" : { "type" : "boolean" },
          "ToFrom" : { "type" : "anonymous395" },
          "ApproximateDistanceInd" : { "type" : "boolean" }
        }
      },
      "TransportationsType" : {
        "label" : "TransportationsType",
        "property info" : { "Transportations" : { "type" : "list\\u003CTransportationTypeTransportation\\u003E" } }
      },
      "ArrayOfTransportationTypeTransportation" : {
        "label" : "ArrayOfTransportationTypeTransportation",
        "property info" : { "Transportation" : { "type" : "Transportation" } }
      },
      "Transportation" : {
        "label" : "Transportation",
        "property info" : {
          "MultimediaDescriptions" : { "type" : "MultimediaDescriptionsType" },
          "OperationSchedules" : { "type" : "OperationSchedulesType" },
          "DescriptiveText" : { "type" : "text" },
          "NotificationRequired" : { "type" : "text" },
          "TransportationCode" : { "type" : "text" },
          "ChargeUnit" : { "type" : "text" },
          "Included" : { "type" : "boolean" },
          "CodeDetail" : { "type" : "text" },
          "Description" : { "type" : "text" },
          "TypicalTravelTime" : { "type" : "text" },
          "Amount" : { "type" : "decimal" },
          "ExistsCode" : { "type" : "text" }
        }
      },
      "OperationSchedulesType" : {
        "label" : "OperationSchedulesType",
        "property info" : {
          "OperationSchedule" : { "type" : "OperationScheduleType" },
          "Start" : { "type" : "text" },
          "Duration" : { "type" : "text" },
          "End" : { "type" : "text" },
          "Release" : { "type" : "text" }
        }
      },
      "OperationScheduleType" : {
        "label" : "OperationScheduleType",
        "property info" : {
          "OperationTimes" : { "type" : "list\\u003COperationScheduleTypeOperationTime\\u003E" },
          "Start" : { "type" : "text" },
          "Duration" : { "type" : "text" },
          "End" : { "type" : "text" },
          "Release" : { "type" : "text" }
        }
      },
      "ArrayOfOperationScheduleTypeOperationTime" : {
        "label" : "ArrayOfOperationScheduleTypeOperationTime",
        "property info" : { "OperationTime" : { "type" : "OperationTime" } }
      },
      "OperationTime" : {
        "label" : "OperationTime",
        "property info" : {
          "Mon" : { "type" : "boolean" },
          "Tue" : { "type" : "boolean" },
          "Weds" : { "type" : "boolean" },
          "Thur" : { "type" : "boolean" },
          "Fri" : { "type" : "boolean" },
          "Sat" : { "type" : "boolean" },
          "Sun" : { "type" : "boolean" },
          "Start" : { "type" : "text" },
          "Duration" : { "type" : "text" },
          "End" : { "type" : "text" },
          "Release" : { "type" : "text" },
          "AdditionalOperationInfoCode" : { "type" : "text" },
          "Frequency" : { "type" : "text" },
          "Text" : { "type" : "text" }
        }
      },
      "OperationSchedulePlusChargeType" : {
        "label" : "OperationSchedulePlusChargeType",
        "property info" : { "Charge" : { "type" : "FeeType" } }
      },
      "ArrayOfOperationSchedulesPlusChargeTypeOperationSchedule" : {
        "label" : "ArrayOfOperationSchedulesPlusChargeTypeOperationSchedule",
        "property info" : { "OperationSchedule" : { "type" : "OperationSchedule" } }
      },
      "OperationSchedule" : {
        "label" : "OperationSchedule",
        "property info" : { "Name" : { "type" : "text" } }
      },
      "ArrayOfFeaturesTypeFeature" : {
        "label" : "ArrayOfFeaturesTypeFeature",
        "property info" : { "Feature" : { "type" : "Feature" } }
      },
      "Feature" : {
        "label" : "Feature",
        "property info" : {
          "Charge" : { "type" : "Charge" },
          "MultimediaDescriptions" : { "type" : "MultimediaDescriptionsType" },
          "DescriptiveText" : { "type" : "text" },
          "CodeDetail" : { "type" : "text" },
          "AccessibleCode" : { "type" : "text" },
          "SecurityCode" : { "type" : "text" },
          "ExistsCode" : { "type" : "text" },
          "ProximityCode" : { "type" : "text" }
        }
      },
      "Charge" : {
        "label" : "Charge",
        "property info" : { "Amount" : { "type" : "decimal" } }
      },
      "ArrayOfRateRangeType" : {
        "label" : "ArrayOfRateRangeType",
        "property info" : { "RateRange" : { "type" : "RateRangeType" } }
      },
      "RateRangeType" : {
        "label" : "RateRangeType",
        "property info" : {
          "StayRequirement" : { "type" : "StayRequirementType" },
          "Start" : { "type" : "text" },
          "Duration" : { "type" : "text" },
          "End" : { "type" : "text" },
          "Release" : { "type" : "text" },
          "RateType" : { "type" : "RateTypeType" },
          "MinRate" : { "type" : "decimal" },
          "MaxRate" : { "type" : "decimal" },
          "FixedRate" : { "type" : "decimal" },
          "FullRate" : { "type" : "decimal" },
          "RateTimeUnit" : { "type" : "TimeUnitType" },
          "MinRent" : { "type" : "decimal" },
          "MaxRent" : { "type" : "decimal" },
          "FixedRent" : { "type" : "decimal" },
          "FullRent" : { "type" : "decimal" },
          "MinFees" : { "type" : "decimal" },
          "MaxFees" : { "type" : "decimal" },
          "FixedFees" : { "type" : "decimal" },
          "FullFees" : { "type" : "decimal" },
          "MinTax" : { "type" : "decimal" },
          "MaxTax" : { "type" : "decimal" },
          "FixedTax" : { "type" : "decimal" },
          "FullTax" : { "type" : "decimal" },
          "SeasonName" : { "type" : "text" }
        }
      },
      "ArrayOfEVRN_PoliciesTypePolicy" : {
        "label" : "ArrayOfEVRN_PoliciesTypePolicy",
        "property info" : { "Policy" : { "type" : "Policy" } }
      },
      "Policy" : {
        "label" : "Policy",
        "property info" : {
          "PolicyInfo" : { "type" : "PolicyInfo" },
          "PetsPolicies" : { "type" : "PetsPoliciesType" },
          "StayRequirements" : { "type" : "list\\u003CStayRequirementType\\u003E" },
          "CommissionPolicies" : { "type" : "CommissionPoliciesType" },
          "CancelPolicy" : { "type" : "CancelPenaltiesType" },
          "RentalAgreement" : { "type" : "list\\u003CParagraphType\\u003E" },
          "GuaranteePaymentPolicy" : { "type" : "list\\u003CRequiredPaymentsTypeGuaranteePayment\\u003E" },
          "DefaultValidBookingMinOffset" : { "type" : "nonNegativeInteger" },
          "Start" : { "type" : "text" },
          "Duration" : { "type" : "text" },
          "End" : { "type" : "text" },
          "Release" : { "type" : "text" },
          "Code" : { "type" : "text" },
          "CodeDetail" : { "type" : "text" },
          "LastUpdated" : { "type" : "dateTime" },
          "Mon" : { "type" : "boolean" },
          "Tue" : { "type" : "boolean" },
          "Weds" : { "type" : "boolean" },
          "Thur" : { "type" : "boolean" },
          "Fri" : { "type" : "boolean" },
          "Sat" : { "type" : "boolean" },
          "Sun" : { "type" : "boolean" }
        }
      },
      "PolicyInfo" : {
        "label" : "PolicyInfo",
        "property info" : {
          "Description" : { "type" : "ParagraphType" },
          "CheckInTime" : { "type" : "text" },
          "CheckOutTime" : { "type" : "text" },
          "SmokingAllowed" : { "type" : "boolean" },
          "TotalGuestCount" : { "type" : "nonNegativeInteger" }
        }
      },
      "CommissionPoliciesType" : {
        "label" : "CommissionPoliciesType",
        "property info" : {
          "CommissionPolicy" : { "type" : "CommissionPolicyType" },
          "MinCommissionPercent" : { "type" : "decimal" },
          "MaxCommissionPercent" : { "type" : "decimal" }
        }
      },
      "UnitReviewsType" : {
        "label" : "UnitReviewsType",
        "property info" : {
          "UnitReview" : { "type" : "UnitReviewType" },
          "PropertyManagerReview" : { "type" : "PropertyManagerReviewType" }
        }
      },
      "UnitReviewType" : {
        "label" : "UnitReviewType",
        "property info" : {
          "ReviewScore" : { "type" : "ReviewScoreType" },
          "ReviewComment" : { "type" : "ReviewCommentType" },
          "ManagerResponse" : { "type" : "ManagerResponseType" },
          "Title" : { "type" : "text" },
          "ReviewedDate" : { "type" : "dateTime" },
          "LastUpdated" : { "type" : "dateTime" },
          "ReviewerID" : { "type" : "text" },
          "ReviewerName" : { "type" : "text" },
          "ReviewerCity" : { "type" : "text" },
          "ReviewerState" : { "type" : "text" },
          "ReviewerCountry" : { "type" : "text" },
          "ReviewerEmail" : { "type" : "text" },
          "CheckIn" : { "type" : "date" },
          "CheckOut" : { "type" : "date" },
          "PropertyManagerRejected" : { "type" : "boolean" },
          "ReservationNumber" : { "type" : "text" }
        }
      },
      "ReviewScoreType" : {
        "label" : "ReviewScoreType",
        "property info" : {
          "Score" : { "type" : "decimal" },
          "CategoryID" : { "type" : "integer" },
          "CategoryName" : { "type" : "text" },
          "CategoryType" : { "type" : "unsignedByte" },
          "SortOrder" : { "type" : "integer" }
        }
      },
      "ReviewCommentType" : {
        "label" : "ReviewCommentType",
        "property info" : {
          "Comment" : { "type" : "text" },
          "CategoryID" : { "type" : "integer" },
          "CategoryName" : { "type" : "text" },
          "CategoryType" : { "type" : "byte" },
          "SortOrder" : { "type" : "integer" }
        }
      },
      "ManagerResponseType" : {
        "label" : "ManagerResponseType",
        "property info" : {
          "ResponseDate" : { "type" : "dateTime" },
          "ResponseTitle" : { "type" : "text" },
          "Comment" : { "type" : "text" }
        }
      },
      "PropertyManagerReviewType" : {
        "label" : "PropertyManagerReviewType",
        "property info" : {
          "AverageReviewScore" : { "type" : "ReviewScoreType" },
          "ReviewCount" : { "type" : "integer" }
        }
      },
      "PromotionsType" : {
        "label" : "PromotionsType",
        "property info" : {
          "RateDiscount" : { "type" : "RateDiscountType" },
          "LastUpdated" : { "type" : "dateTime" }
        }
      },
      "ItemSearchCriterionType" : {
        "label" : "ItemSearchCriterionType",
        "property info" : {
          "Position" : { "type" : "Position" },
          "Address" : { "type" : "Address" },
          "UnitRef" : { "type" : "UnitRef" },
          "Radius" : { "type" : "Radius" },
          "Region" : { "type" : "RegionType" },
          "ExactMatch" : { "type" : "boolean" },
          "ImportanceType" : { "type" : "anonymous434" },
          "Ranking" : { "type" : "integer" }
        }
      },
      "UnitRef" : {
        "label" : "UnitRef",
        "property info" : {
          "PropertyManagerCode" : { "type" : "text" },
          "UnitCode" : { "type" : "text" },
          "UnitName" : { "type" : "text" },
          "InfoSource" : { "type" : "text" },
          "InternalUnitCode" : { "type" : "text" },
          "UnitHeadline" : { "type" : "text" },
          "PropertyURL" : { "type" : "text" }
        }
      },
      "Radius" : {
        "label" : "Radius",
        "property info" : {
          "Distance" : { "type" : "text" },
          "DistanceMeasure" : { "type" : "text" },
          "Direction" : { "type" : "text" },
          "DistanceMax" : { "type" : "text" }
        }
      },
      "RegionType" : {
        "label" : "RegionType",
        "property info" : {
          "CountryCode" : { "type" : "text" },
          "PostalCode" : { "type" : "text" }
        }
      },
      "RegionIdentifierType" : {
        "label" : "RegionIdentifierType",
        "property info" : {
          "RegionCode" : { "type" : "integer" },
          "RegionName" : { "type" : "text" },
          "RegionFriendlyName" : { "type" : "text" }
        }
      },
      "Areas" : {
        "label" : "Areas",
        "property info" : {
          "Area" : { "type" : "SearchAreaType" },
          "PlaceHolder" : { "type" : "integer" }
        }
      },
      "SearchAreaType" : {
        "label" : "SearchAreaType",
        "property info" : {
          "UnitCount" : { "type" : "UnitCount" },
          "ZipList" : { "type" : "anonymous443" },
          "MinDiscount" : { "type" : "decimal" },
          "MaxDiscount" : { "type" : "decimal" },
          "StartDate" : { "type" : "date" },
          "EndDate" : { "type" : "date" }
        }
      },
      "UnitCount" : {
        "label" : "UnitCount",
        "property info" : { "InfoSource" : { "type" : "text" }, "Count" : { "type" : "integer" } }
      },
      "AreaType" : {
        "label" : "AreaType",
        "property info" : {
          "AreaDescription" : { "type" : "ParagraphType" },
          "AreaID" : { "type" : "text" },
          "City" : { "type" : "text" },
          "CityCode" : { "type" : "text" },
          "StateProv" : { "type" : "text" },
          "StateProvCode" : { "type" : "text" },
          "CountryCode" : { "type" : "text" }
        }
      },
      "EVRN_UnitCalendarAvailRS" : {
        "label" : "EVRN_UnitCalendarAvailRS",
        "property info" : {
          "Errors" : { "type" : "ErrorsType" },
          "UnitCalendarAvailSegments" : { "type" : "UnitCalendarAvailSegments" },
          "Success" : { "type" : "SuccessType" },
          "Warnings" : { "type" : "WarningsType" }
        }
      },
      "UnitCalendarAvailSegments" : {
        "label" : "UnitCalendarAvailSegments",
        "property info" : {
          "UnitCalendarAvailSegment" : { "type" : "UnitCalendarAvailSegment" },
          "PropertyManagerCode" : { "type" : "text" },
          "UnitCode" : { "type" : "text" },
          "UnitName" : { "type" : "text" },
          "InfoSource" : { "type" : "text" },
          "InternalUnitCode" : { "type" : "text" },
          "UnitHeadline" : { "type" : "text" },
          "PropertyURL" : { "type" : "text" }
        }
      },
      "UnitCalendarAvailSegment" : {
        "label" : "UnitCalendarAvailSegment",
        "property info" : {
          "DailyAvailability" : { "type" : "text" },
          "StayRequirements" : { "type" : "list\\u003CStayRequirementType\\u003E" },
          "DailyMinLOS" : { "type" : "text" },
          "StartDate" : { "type" : "date" },
          "EndDate" : { "type" : "date" }
        }
      },
      "DepositPayments" : {
        "label" : "DepositPayments",
        "property info" : { "SendData" : { "type" : "boolean" } }
      },
      "CancelPenalties" : {
        "label" : "CancelPenalties",
        "property info" : { "SendData" : { "type" : "boolean" } }
      },
      "BasicUnitInfo" : {
        "label" : "BasicUnitInfo",
        "property info" : { "SendData" : { "type" : "boolean" } }
      },
      "RentalAgreement" : {
        "label" : "RentalAgreement",
        "property info" : { "SendData" : { "type" : "boolean" } }
      },
      "EVRN_UnitStayRS" : {
        "label" : "EVRN_UnitStayRS",
        "property info" : {
          "UnitStay" : { "type" : "UnitStayType" },
          "Errors" : { "type" : "ErrorsType" },
          "Success" : { "type" : "SuccessType" },
          "TPA_Extensions" : { "type" : "TPA_Extensions_Type" },
          "Warnings" : { "type" : "WarningsType" }
        }
      },
      "EVRN_UnitReadRQ" : {
        "label" : "EVRN_UnitReadRQ",
        "property info" : {
          "UniqueID" : { "type" : "UniqueID_Type" },
          "ReadRequests" : { "type" : "ReadRequests" },
          "ReqRespVersion" : { "type" : "text" },
          "ReservationType" : { "type" : "text" },
          "ReturnListIndicator" : { "type" : "boolean" },
          "MoreIndicator" : { "type" : "boolean" },
          "MoreDataEchoToken" : { "type" : "text" }
        }
      },
      "ReadRequests" : {
        "label" : "ReadRequests",
        "property info" : {
          "GlobalReservationReadRequest" : { "type" : "GlobalReservationReadRequest" },
          "ReadRequest" : { "type" : "ReadRequest" }
        }
      },
      "GlobalReservationReadRequest" : {
        "label" : "GlobalReservationReadRequest",
        "property info" : {
          "TravelerName" : { "type" : "PersonNameType" },
          "Start" : { "type" : "text" },
          "Duration" : { "type" : "text" },
          "End" : { "type" : "text" },
          "Release" : { "type" : "text" }
        }
      },
      "ReadRequest" : {
        "label" : "ReadRequest",
        "property info" : {
          "UniqueID" : { "type" : "UniqueID_Type" },
          "Verification" : { "type" : "VerificationType" },
          "HistoryRequestedInd" : { "type" : "boolean" },
          "startDate" : { "type" : "dateTime" },
          "endDate" : { "type" : "dateTime" },
          "requestDateType" : { "type" : "text" },
          "summaryOnly" : { "type" : "boolean" },
          "maxResults" : { "type" : "integer" }
        }
      },
      "VerificationType" : {
        "label" : "VerificationType",
        "property info" : {
          "PersonName" : { "type" : "PersonName" },
          "Email" : { "type" : "EmailType" },
          "TelephoneInfo" : { "type" : "TelephoneInfo" },
          "PaymentCard" : { "type" : "PaymentCardType" },
          "AddressInfo" : { "type" : "AddressInfoType" },
          "CustLoyalty" : { "type" : "CustLoyalty" },
          "Vendor" : { "type" : "CompanyNameType" },
          "ReservationTimeSpan" : { "type" : "ReservationTimeSpan" },
          "AssociatedQuantity" : { "type" : "AssociatedQuantity" },
          "StartLocation" : { "type" : "StartLocation" },
          "EndLocation" : { "type" : "EndLocation" },
          "TPA_Extensions" : { "type" : "TPA_Extensions_Type" }
        }
      },
      "PersonName" : {
        "label" : "PersonName",
        "property info" : { "PartialName" : { "type" : "boolean" } }
      },
      "TelephoneInfo" : {
        "label" : "TelephoneInfo",
        "property info" : {
          "ShareSynchInd" : { "type" : "anonymous467" },
          "ShareMarketInd" : { "type" : "anonymous468" },
          "PhoneLocationType" : { "type" : "text" },
          "PhoneTechType" : { "type" : "text" },
          "PhoneUseType" : { "type" : "text" },
          "CountryAccessCode" : { "type" : "text" },
          "AreaCityCode" : { "type" : "text" },
          "PhoneNumber" : { "type" : "text" },
          "Extension" : { "type" : "text" },
          "PIN" : { "type" : "text" },
          "FormattedInd" : { "type" : "boolean" },
          "DefaultInd" : { "type" : "boolean" },
          "RPH" : { "type" : "text" }
        }
      },
      "ReservationTimeSpan" : {
        "label" : "ReservationTimeSpan",
        "property info" : {
          "Start" : { "type" : "text" },
          "Duration" : { "type" : "text" },
          "End" : { "type" : "text" },
          "Release" : { "type" : "text" }
        }
      },
      "AssociatedQuantity" : {
        "label" : "AssociatedQuantity",
        "property info" : { "URI" : { "type" : "anyURI" } }
      },
      "StartLocation" : {
        "label" : "StartLocation",
        "property info" : {
          "_" : { "type" : "LocationType" },
          "AssociatedDateTime" : { "type" : "dateTime" }
        }
      },
      "EndLocation" : {
        "label" : "EndLocation",
        "property info" : {
          "_" : { "type" : "LocationType" },
          "AssociatedDateTime" : { "type" : "dateTime" }
        }
      },
      "EVRN_UnitInquiryRQ" : {
        "label" : "EVRN_UnitInquiryRQ",
        "property info" : { "InquiryRequests" : { "type" : "list\\u003CInquiryRequestType\\u003E" } }
      },
      "ArrayOfInquiryRequestType" : {
        "label" : "ArrayOfInquiryRequestType",
        "property info" : { "InquiryRequest" : { "type" : "InquiryRequestType" } }
      },
      "InquiryRequestType" : {
        "label" : "InquiryRequestType",
        "property info" : {
          "UnitRef" : { "type" : "UnitRef" },
          "Contact" : { "type" : "Contact" },
          "Message" : { "type" : "FormattedTextTextType" },
          "Source" : { "type" : "Source" },
          "StayDateRange" : { "type" : "DateTimeSpanType" },
          "GuestCounts" : { "type" : "GuestCountType" },
          "InquiryType" : { "type" : "text" },
          "InquiryDate" : { "type" : "dateTime" },
          "TransactionIdentifier" : { "type" : "text" }
        }
      },
      "Contact" : {
        "label" : "Contact",
        "property info" : {
          "Name" : { "type" : "PersonNameType" },
          "Email" : { "type" : "EmailType" },
          "Telephone" : { "type" : "TelephoneInfoType" },
          "PreferredContactMethod" : { "type" : "PreferredContactMethodType" },
          "IPAddress" : { "type" : "text" }
        }
      },
      "Source" : {
        "label" : "Source",
        "property info" : { "UnitDescriptionURL" : { "type" : "text" } }
      },
      "EVRN_UnitInquiryRS" : {
        "label" : "EVRN_UnitInquiryRS",
        "property info" : {
          "Warnings" : { "type" : "WarningsType" },
          "Errors" : { "type" : "ErrorsType" },
          "Success" : { "type" : "SuccessType" },
          "TPA_Extensions" : { "type" : "TPA_Extensions_Type" }
        }
      },
      "EVRN_UnitCalendarAvailBatchRQ" : {
        "label" : "EVRN_UnitCalendarAvailBatchRQ",
        "property info" : {
          "CalenadAvails" : { "type" : "list\\u003CCalendarAvailType\\u003E" },
          "SummaryOnly" : { "type" : "boolean" },
          "ShowHold" : { "type" : "boolean" }
        }
      },
      "ArrayOfCalendarAvailType" : {
        "label" : "ArrayOfCalendarAvailType",
        "property info" : { "CalendarAvail" : { "type" : "CalendarAvailType" } }
      },
      "CalendarAvailType" : {
        "label" : "CalendarAvailType",
        "property info" : {
          "CalendarDateRange" : { "type" : "DateTimeSpanType" },
          "PropertyManagerCode" : { "type" : "text" },
          "UnitCode" : { "type" : "text" },
          "UnitName" : { "type" : "text" },
          "InfoSource" : { "type" : "text" },
          "InternalUnitCode" : { "type" : "text" },
          "UnitHeadline" : { "type" : "text" },
          "PropertyURL" : { "type" : "text" },
          "StateCodeList" : { "type" : "anonymous486" },
          "CountryCodeList" : { "type" : "anonymous487" },
          "UpdatedAfter" : { "type" : "dateTime" }
        }
      },
      "EVRN_CampaignRQ" : {
        "label" : "EVRN_CampaignRQ",
        "property info" : { "CampaignRequests" : { "type" : "list\\u003CCampaignRequestType\\u003E" } }
      },
      "ArrayOfCampaignRequestType" : {
        "label" : "ArrayOfCampaignRequestType",
        "property info" : { "CampaignRequest" : { "type" : "CampaignRequestType" } }
      },
      "CampaignRequestType" : {
        "label" : "CampaignRequestType",
        "property info" : {
          "IsActive" : { "type" : "boolean" },
          "IsDeleted" : { "type" : "boolean" }
        }
      },
      "EVRN_CampaignRS" : {
        "label" : "EVRN_CampaignRS",
        "property info" : {
          "Success" : { "type" : "SuccessType" },
          "Warnings" : { "type" : "WarningsType" },
          "Campaigns" : { "type" : "Campaigns" },
          "TPA_Extensions" : { "type" : "TPA_Extensions_Type" },
          "Errors" : { "type" : "ErrorsType" }
        }
      },
      "Campaigns" : {
        "label" : "Campaigns",
        "property info" : { "Campaign" : { "type" : "CampaignType" } }
      },
      "CampaignType" : {
        "label" : "CampaignType",
        "property info" : {
          "CampaignKeywordReferral" : { "type" : "CampaignKeywordReferralType" },
          "Campaign_ID" : { "type" : "integer" },
          "TollFreeNumber" : { "type" : "text" },
          "CreationDate" : { "type" : "text" },
          "EffectiveDate" : { "type" : "date" },
          "ExpirationDate" : { "type" : "date" },
          "UpdatedDate" : { "type" : "text" },
          "Name" : { "type" : "text" },
          "IsActive" : { "type" : "boolean" },
          "IsDeleted" : { "type" : "boolean" }
        }
      },
      "CampaignKeywordReferralType" : {
        "label" : "CampaignKeywordReferralType",
        "property info" : {
          "ReferralHost" : { "type" : "text" },
          "KeywordName" : { "type" : "text" },
          "KeywordValue" : { "type" : "text" }
        }
      },
      "EVRN_PropertyManagerRQ" : {
        "label" : "EVRN_PropertyManagerRQ",
        "property info" : { "PropertyManagerRequests" : { "type" : "PropertyManagerRequests" } }
      },
      "PropertyManagerRequests" : {
        "label" : "PropertyManagerRequests",
        "property info" : { "PropertyManagerRequest" : { "type" : "PropertyManagerRequestType" } }
      },
      "PropertyManagerRequestType" : {
        "label" : "PropertyManagerRequestType",
        "property info" : {
          "PropertyManagerCode" : { "type" : "text" },
          "CountryCodeList" : { "type" : "anonymous498" },
          "StateCodeList" : { "type" : "anonymous499" }
        }
      },
      "EVRN_PropertyManagerRS" : {
        "label" : "EVRN_PropertyManagerRS",
        "property info" : {
          "Warnings" : { "type" : "WarningsType" },
          "Errors" : { "type" : "ErrorsType" },
          "TPA_Extensions" : { "type" : "TPA_Extensions_Type" },
          "PropertyManagers" : { "type" : "PropertyManagers" },
          "Success" : { "type" : "SuccessType" }
        }
      },
      "PropertyManagers" : {
        "label" : "PropertyManagers",
        "property info" : { "PropertyManager" : { "type" : "PropertyManagerType" } }
      },
      "EVRN_UnitHoldRQ" : {
        "label" : "EVRN_UnitHoldRQ",
        "property info" : {
          "UnitCode" : { "type" : "text" },
          "HoldType" : { "type" : "text" },
          "HoldID" : { "type" : "integer" },
          "StartDate" : { "type" : "text" },
          "EndDate" : { "type" : "text" },
          "ReleaseDate" : { "type" : "text" },
          "FirstName" : { "type" : "text" },
          "LastName" : { "type" : "text" },
          "Email" : { "type" : "text" },
          "HoldNumber" : { "type" : "text" },
          "PhoneNumber" : { "type" : "text" },
          "Notes" : { "type" : "text" },
          "RequestType" : { "type" : "text" }
        }
      },
      "EVRN_UnitHoldRS" : {
        "label" : "EVRN_UnitHoldRS",
        "property info" : {
          "Warnings" : { "type" : "WarningsType" },
          "UnitHolds" : { "type" : "UnitHolds" },
          "Success" : { "type" : "SuccessType" },
          "TPA_Extensions" : { "type" : "TPA_Extensions_Type" },
          "Errors" : { "type" : "ErrorsType" }
        }
      },
      "UnitHolds" : {
        "label" : "UnitHolds",
        "property info" : {
          "UnitCode" : { "type" : "text" },
          "FirstName" : { "type" : "text" },
          "LastName" : { "type" : "text" },
          "Notes" : { "type" : "text" },
          "Email" : { "type" : "text" },
          "PhoneNumber" : { "type" : "text" },
          "CreateDateTime" : { "type" : "text" },
          "Timespan" : { "type" : "DateTimeSpanType" },
          "ID" : { "type" : "integer" },
          "Type" : { "type" : "text" },
          "Number" : { "type" : "text" }
        }
      },
      "EVRN_ReservationCancelRQ" : {
        "label" : "EVRN_ReservationCancelRQ",
        "property info" : {
          "UnitCode" : { "type" : "text" },
          "AgentID" : { "type" : "text" },
          "ReservationID" : { "type" : "text" }
        }
      },
      "EVRN_ReservationCancelRS" : {
        "label" : "EVRN_ReservationCancelRS",
        "property info" : {
          "ReservationID" : { "type" : "text" },
          "ReservationStatusTypes" : { "type" : "text" },
          "Message" : { "type" : "text" },
          "TPA_Extensions" : { "type" : "TPA_Extensions_Type" },
          "Warnings" : { "type" : "WarningsType" },
          "Errors" : { "type" : "ErrorsType" },
          "Success" : { "type" : "SuccessType" }
        }
      },
      "EVRN_ReservationUpdateRQ" : {
        "label" : "EVRN_ReservationUpdateRQ",
        "property info" : {
          "BookingNumber" : { "type" : "text" },
          "AgentID" : { "type" : "text" },
          "UnitCode" : { "type" : "text" },
          "NewUnitCode" : { "type" : "text" },
          "StartDate" : { "type" : "text" },
          "EndDate" : { "type" : "text" },
          "RecalculateRate" : { "type" : "text" },
          "Preview" : { "type" : "text" }
        }
      },
      "EVRN_ReservationUpdateRS" : {
        "label" : "EVRN_ReservationUpdateRS",
        "property info" : {
          "Warnings" : { "type" : "WarningsType" },
          "Success" : { "type" : "SuccessType" },
          "TPA_Extensions" : { "type" : "TPA_Extensions_Type" },
          "ReservationUpdate" : { "type" : "ReservationUpdate" },
          "Errors" : { "type" : "ErrorsType" }
        }
      },
      "ReservationUpdate" : {
        "label" : "ReservationUpdate",
        "property info" : {
          "ReservationID" : { "type" : "text" },
          "UnitID" : { "type" : "text" },
          "AgencyID" : { "type" : "text" },
          "StartDate" : { "type" : "text" },
          "EndDate" : { "type" : "text" },
          "BookingNumber" : { "type" : "text" },
          "CreationDate" : { "type" : "text" },
          "ReservationType" : { "type" : "text" },
          "UnitRates" : { "type" : "list\\u003CReservationUpdateUnitRate\\u003E" }
        }
      },
      "ArrayOfReservationUpdateUnitRate" : {
        "label" : "ArrayOfReservationUpdateUnitRate",
        "property info" : { "UnitRate" : { "type" : "UnitRate" } }
      },
      "ArrayOfUnitSearchCriterionType" : {
        "label" : "ArrayOfUnitSearchCriterionType",
        "property info" : { "Criterion" : { "type" : "UnitSearchCriterionType", "label" : "", "allow null" : 0 } }
      },
      "DateTimeSpanType" : {
        "label" : "DateTimeSpanType",
        "property info" : {
          "DateWindowRange" : { "type" : "TimeInstantType", "label" : "", "allow null" : 1 },
          "StartDateWindow" : { "type" : "StartDateWindow", "label" : "", "allow null" : 1 },
          "EndDateWindow" : { "type" : "EndDateWindow", "label" : "", "allow null" : 1 },
          "Start" : { "type" : "text", "label" : "", "allow null" : 1 },
          "Duration" : { "type" : "text", "label" : "", "allow null" : 1 },
          "End" : { "type" : "text", "label" : "", "allow null" : 1 },
          "Release" : { "type" : "text", "label" : "", "allow null" : 1 }
        },
        "name" : "DateTimeSpanType"
      },
      "EVRN_UnitSearchRQ" : {
        "label" : "EVRN_UnitSearchRQ",
        "property info" : {
          "Criteria" : { "type" : "UnitSearchCriteriaType", "label" : "", "allow null" : 0 },
          "MaxResponses" : { "type" : "integer", "label" : "", "allow null" : 1 },
          "SortOrder" : { "type" : "text", "label" : "", "allow null" : 1 },
          "SendRateDetails" : { "type" : "boolean", "label" : "", "allow null" : 0 },
          "SendUnitSummary" : { "type" : "boolean", "label" : "", "allow null" : 0 },
          "PictureSize" : { "type" : "text", "label" : "", "allow null" : 0 },
          "ResponseType" : { "type" : "text", "label" : "", "allow null" : 0 },
          "POS" : { "type" : "list\\u003CSourceType\\u003E" },
          "Version" : { "type" : "decimal", "label" : "", "allow null" : 0 }
        },
        "name" : "EVRN_UnitSearchRQ"
      },
      "UnitSearchCriteriaType" : {
        "label" : "UnitSearchCriteriaType",
        "property info" : {
          "Criterion" : { "type" : "list\\u003CUnitSearchCriterionType\\u003E" },
          "AvailableOnlyIndicator" : { "type" : "boolean", "label" : "", "allow null" : 0 }
        },
        "name" : "UnitSearchCriteriaType"
      },
      "UnitSearchCriterionType" : {
        "label" : "UnitSearchCriterionType",
        "property info" : {
          "Region" : { "type" : "RegionType", "label" : "", "allow null" : 0 },
          "LastMinuteDiscountRange" : { "type" : "LastMinuteDiscountRangeType", "label" : "", "allow null" : 1 },
          "Address" : { "type" : "AddressType", "label" : "", "allow null" : 0 },
          "UnitRef" : { "type" : "UnitRef", "label" : "", "allow null" : 1 },
          "UnitAmenity" : { "type" : "UnitAmenityType", "label" : "", "allow null" : 1 }
        },
        "name" : "UnitSearchCriterionType"
      },
      "EVRN_UnitDescriptiveInfoRQ" : {
        "label" : "EVRN_UnitDescriptiveInfoRQ",
        "property info" : {
          "UnitDescriptiveInfos" : { "type" : "list\\u003CUnitDescriptiveInfoRequestType\\u003E" },
          "SummaryOnly" : { "type" : "boolean", "label" : "", "allow null" : 0 },
          "POS" : { "type" : "list\\u003CSourceType\\u003E" },
          "Version" : { "type" : "decimal", "label" : "", "allow null" : 0 }
        },
        "name" : "EVRN_UnitDescriptiveInfoRQ"
      },
      "UnitsType" : {
        "label" : "UnitsType",
        "property info" : { "Unit" : { "type" : "UnitValueMatchType", "label" : "", "allow null" : 0 } },
        "name" : "UnitsType"
      },
      "Unit" : {
        "label" : "Unit",
        "property info" : {
          "Address" : { "type" : "AddressType", "label" : "", "allow null" : 0 },
          "UnitAmenity" : { "type" : "UnitAmenityType", "label" : "", "allow null" : 0 },
          "MaxOccupancy" : { "type" : "integer", "label" : "", "allow null" : 0 },
          "UnitCode" : { "type" : "text", "label" : "", "allow null" : 0 },
          "UnitName" : { "type" : "text", "label" : "", "allow null" : 0 }
        },
        "name" : "UnitType"
      },
      "Units" : {
        "label" : "Units",
        "property info" : {
          "moredata" : { "type" : "boolean", "label" : "", "allow null" : 0 },
          "Unit" : { "type" : "list\\u003CUnit\\u003E" }
        },
        "name" : "Units"
      },
      "EVRN_UnitSearchRS" : {
        "label" : "EVRN_UnitSearchRS",
        "property info" : {
          "TPA_Extensions" : { "type" : "TPA_Extensions_Type", "label" : "", "allow null" : 0 },
          "Criteria" : { "type" : "UnitSearchCriteriaType", "label" : "", "allow null" : 0 },
          "Errors" : { "type" : "ErrorsType", "label" : "", "allow null" : 0 },
          "Success" : { "type" : "SuccessType", "label" : "", "allow null" : 0 },
          "Warnings" : { "type" : "WarningsType", "label" : "", "allow null" : 0 },
          "Units" : { "type" : "list\\u003CUnit\\u003E" },
          "Areas" : { "type" : "Areas", "label" : "", "allow null" : 0 }
        },
        "name" : "EVRN_UnitSearchRS"
      },
      "EVRN_UnitCalendarAvailRQ" : {
        "label" : "EVRN_UnitCalendarAvailRQ",
        "property info" : {
          "UnitRef" : { "type" : "UnitRef", "label" : "", "allow null" : 0 },
          "CalendarDateRange" : { "type" : "DateTimeSpanType", "label" : "", "allow null" : 0 },
          "ShowHolds" : { "type" : "text", "label" : "", "allow null" : 0 },
          "POS" : { "type" : "list\\u003CSourceType\\u003E" },
          "Version" : { "type" : "decimal", "label" : "", "allow null" : 0 }
        },
        "name" : "EVRN_UnitCalendarAvailRQ"
      },
      "EVRN_UnitStayRQ" : {
        "label" : "EVRN_UnitStayRQ",
        "property info" : {
          "UnitStay" : { "type" : "UnitStay", "label" : "", "allow null" : 0 },
          "POS" : { "type" : "list\\u003CSourceType\\u003E" },
          "Version" : { "type" : "decimal", "label" : "", "allow null" : 0 }
        },
        "name" : "EVRN_UnitStayRQ"
      },
      "UnitStay" : {
        "label" : "UnitStay",
        "property info" : {
          "UnitRef" : { "type" : "UnitRef", "label" : "", "allow null" : 0 },
          "StayDateRange" : { "type" : "DateTimeSpanType", "label" : "", "allow null" : 0 },
          "GuestCounts" : { "type" : "GuestCountType", "label" : "", "allow null" : 0 },
          "DepositPayments" : { "type" : "DepositPayments", "label" : "", "allow null" : 0 },
          "CancelPenalties" : { "type" : "CancelPenalties", "label" : "", "allow null" : 0 },
          "BasicUnitInfo" : { "type" : "BasicUnitInfo", "label" : "", "allow null" : 0 },
          "RentalAgreement" : { "type" : "RentalAgreement", "label" : "", "allow null" : 0 },
          "AdditionalCharges" : { "type" : "AdditionalCharges", "label" : "", "allow null" : 0 },
          "AvailableOnlyIndicator" : { "type" : "boolean", "label" : "", "allow null" : 0 }
        },
        "name" : "UnitStay"
      }
    },
    "global_parameters" : {
      "PictureSize" : { "default value" : "Thumbnail" },
      "ResponseType" : { "default value" : "PropertyList" }
    },
    "name" : "escapia_api",
    "label" : "Escapia API (v.1.030)",
    "url" : "https:\\/\\/api.escapia.com\\/EVRNService.svc?wsdl",
    "type" : "soap",
    "authentication" : null
  }');
  return $items;
}
