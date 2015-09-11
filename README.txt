Instructions on setting up Escapia Feed:

ESCAPIA API documentation for reference: https://customer.escapia.com/distribution/api/evrn-api-documentation

1. After enabling escapia_wsclient_feeds feature, there will be configuration created for Feed importers and for WebService Client modules to provide all the
   basic Escapia API functionality for importing units:
   - admin/config/services/wsclient/manage/escapia_api   - contains all the operations / data types based on ESCAPIA WSDL structure (UnitSearch and UnitDescriptiveInfo operations
     are already pre-configured with correct parameters / data structure. Other operations might require some tweaking as they require authentication and some structural changes because
     automatic WSDL import cannot account for all the use cases like multiple values, etc.)

2. Before the Feeds can be utilized, update Authentication Parameters for both of the Escapia Feed Importers at (UI modules for Feeds and WebService Client need to be enabled). Enter user
   name and password under "Web Service Fetcher Settings" Tab within "List of POS (list<SourceType>)[0][RequestorID]" fieldset:
    - admin/structure/feeds/escapia_rentals_descriptive_info/settings/FeedsWSClientFetcher
    - admin/structure/feeds/escapia_rentals_units_search/settings/FeedsWSClientFetcher

3. Escapia API UnitSearch() operation requires at list one Search Criteria to be set. Default configuration for the search is based on ADDRESS parameters, which only has COUNTRY field
   set to "US" value. This configuration will allow to search all of your rental properties within your Escapia Account (of course, if they are located in the USA). Change any
   parameters as necessary.

4. To trigger initial import of Escapia Rental Properties, run UnitsSearch Feed Import from 'import/escapia_rentals_units_search'.