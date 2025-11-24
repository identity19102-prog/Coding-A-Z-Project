// CityData.java
package UniversalTimeIndicator;

import java.util.LinkedHashMap;
import java.util.Map;

public class CityData {
    private Map<String, String> cities = new LinkedHashMap<>();

    public CityData() {
    	 // Africa
        cities.put("Egypt / Cairo", "Africa/Cairo");
        cities.put("Ghana / Accra", "Africa/Accra");
        cities.put("Kenya / Nairobi", "Africa/Nairobi");
        cities.put("Morocco / Casablanca", "Africa/Casablanca");
        cities.put("South Africa / Johannesburg", "Africa/Johannesburg");
        cities.put("Tunisia / Tunis", "Africa/Tunis");

        // Antarctica
        cities.put("Antarctica / McMurdo", "Antarctica/McMurdo");
        cities.put("Antarctica / Palmer", "Antarctica/Palmer");
        cities.put("Antarctica / South Pole", "Antarctica/South_Pole");
        cities.put("Antarctica / Rothera", "Antarctica/Rothera");
        cities.put("Antarctica / Syowa", "Antarctica/Syowa");
        cities.put("Antarctica / Troll", "Antarctica/Troll");
        cities.put("Antarctica / Vostok", "Antarctica/Vostok");

        // Asia
        cities.put("Armenia / Yerevan", "Asia/Yerevan");
        cities.put("Azerbaijan / Baku", "Asia/Baku");
        cities.put("Bangladesh / Dhaka", "Asia/Dhaka");
        cities.put("Bhutan / Thimphu", "Asia/Thimphu");
        cities.put("Brunei / Bandar Seri Begawan", "Asia/Brunei");
        cities.put("Cambodia / Phnom Penh", "Asia/Phnom_Penh");
        cities.put("China / Beijing", "Asia/Shanghai");
        cities.put("China / Guangzhou", "Asia/Shanghai");
        cities.put("China / Shanghai", "Asia/Shanghai");
        cities.put("China / Shenzhen", "Asia/Shanghai");
        cities.put("Hong Kong / Hong Kong", "Asia/Hong_Kong");
        cities.put("India / Bangalore", "Asia/Kolkata");
        cities.put("India / Chennai", "Asia/Kolkata");
        cities.put("India / Delhi", "Asia/Kolkata");
        cities.put("India / Kolkata", "Asia/Kolkata");
        cities.put("India / Mumbai", "Asia/Kolkata");
        cities.put("Indonesia / Jakarta", "Asia/Jakarta");
        cities.put("Israel / Jerusalem", "Asia/Jerusalem");
        cities.put("Japan / Nagoya", "Asia/Tokyo");
        cities.put("Japan / Osaka", "Asia/Tokyo");
        cities.put("Japan / Tokyo", "Asia/Tokyo");
        cities.put("Kazakhstan / Almaty", "Asia/Almaty");
        cities.put("Malaysia / Kuala Lumpur", "Asia/Kuala_Lumpur");
        cities.put("Mongolia / Ulaanbaatar", "Asia/Ulaanbaatar");
        cities.put("Myanmar / Yangon", "Asia/Yangon");
        cities.put("Nepal / Kathmandu", "Asia/Kathmandu");
        cities.put("North Korea / Pyongyang", "Asia/Pyongyang");
        cities.put("Pakistan / Karachi", "Asia/Karachi");
        cities.put("Pakistan / Lahore", "Asia/Karachi");
        cities.put("Philippines / Manila", "Asia/Manila");
        cities.put("Qatar / Doha", "Asia/Qatar");
        cities.put("Saudi Arabia / Riyadh", "Asia/Riyadh");
        cities.put("Singapore / Singapore", "Asia/Singapore");
        cities.put("South Korea / Busan", "Asia/Seoul");
        cities.put("South Korea / Incheon", "Asia/Seoul");
        cities.put("Sri Lanka / Colombo", "Asia/Colombo");
        cities.put("Thailand / Bangkok", "Asia/Bangkok");
        cities.put("Thailand / Chiang Mai", "Asia/Bangkok");
        cities.put("UAE / Dubai", "Asia/Dubai");
        cities.put("Uzbekistan / Tashkent", "Asia/Tashkent");
        cities.put("Vietnam / Hanoi", "Asia/Ho_Chi_Minh");
        cities.put("Vietnam / Ho Chi Minh City", "Asia/Ho_Chi_Minh");

        // Europe
        cities.put("Austria / Vienna", "Europe/Vienna");
        cities.put("Belgium / Brussels", "Europe/Brussels");
        cities.put("Czech Republic / Prague", "Europe/Prague");
        cities.put("Denmark / Copenhagen", "Europe/Copenhagen");
        cities.put("Finland / Helsinki", "Europe/Helsinki");
        cities.put("France / Paris", "Europe/Paris");
        cities.put("Germany / Berlin", "Europe/Berlin");
        cities.put("Greece / Athens", "Europe/Athens");
        cities.put("Iceland / Reykjavik", "Atlantic/Reykjavik");
        cities.put("Ireland / Dublin", "Europe/Dublin");
        cities.put("Italy / Rome", "Europe/Rome");
        cities.put("Netherlands / Amsterdam", "Europe/Amsterdam");
        cities.put("Norway / Oslo", "Europe/Oslo");
        cities.put("Poland / Warsaw", "Europe/Warsaw");
        cities.put("Portugal / Lisbon", "Europe/Lisbon");
        cities.put("Russia / Moscow", "Europe/Moscow");
        cities.put("Russia / Saint Petersburg", "Europe/Moscow");
        cities.put("Spain / Madrid", "Europe/Madrid");
        cities.put("Sweden / Stockholm", "Europe/Stockholm");
        cities.put("Switzerland / Zurich", "Europe/Zurich");
        cities.put("Turkey / Istanbul", "Europe/Istanbul");
        cities.put("UK / London", "Europe/London");

        // America
        cities.put("Argentina / Buenos Aires", "America/Argentina/Buenos_Aires");
        cities.put("Brazil / Rio de Janeiro", "America/Sao_Paulo");
        cities.put("Brazil / Sao Paulo", "America/Sao_Paulo");
        cities.put("Canada / Montreal", "America/Toronto");
        cities.put("Canada / Toronto", "America/Toronto");
        cities.put("Canada / Vancouver", "America/Vancouver");
        cities.put("Chile / Santiago", "America/Santiago");
        cities.put("Colombia / Bogota", "America/Bogota");
        cities.put("Mexico / Guadalajara", "America/Mexico_City");
        cities.put("Mexico / Mexico City", "America/Mexico_City");
        cities.put("Peru / Lima", "America/Lima");
        cities.put("USA / Chicago", "America/Chicago");
        cities.put("USA / Denver", "America/Denver");
        cities.put("USA / Houston", "America/Chicago");
        cities.put("USA / Los Angeles", "America/Los_Angeles");
        cities.put("USA / Miami", "America/New_York");
        cities.put("USA / New York", "America/New_York");
        cities.put("Venezuela / Caracas", "America/Caracas");

        // Pacific / Australia / New Zealand
        cities.put("Australia / Melbourne", "Australia/Melbourne");
        cities.put("Australia / Perth", "Australia/Perth");
        cities.put("Australia / Sydney", "Australia/Sydney");
        cities.put("New Zealand / Auckland", "Pacific/Auckland");
        cities.put("Pacific / Fiji", "Pacific/Fiji");
        cities.put("Pacific / Honolulu", "Pacific/Honolulu");
        cities.put("Pacific / Guam", "Pacific/Guam");
        cities.put("Pacific / Midway", "Pacific/Midway");
        cities.put("Pacific / Samoa", "Pacific/Samoa");
    }
    public Map<String, String> getCities() {
        return cities;
    }
}
