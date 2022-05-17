<?PHP

// Update this array to include the MAC of the device, from which, you wish to accept update requests
$db = array(
  "18:FE:AA:AA:AA:AA" => "ESP32_TempSender",
  "DE:AD:D0:0D:BA:AD" => "Fake-device"
);

/*Example header data:

[HTTP_USER_AGENT] => ESP-http-Update
[HTTP_X_ESP_RUNNING_SHA256] => <uppercase sha256sum here>
[HTTP_X_ESP_STA_MAC] => 18:FE:AA:AA:AA:AA
// The rest are not used in this example
// Retained(ish) from example https://arduino-esp8266.readthedocs.io/en/2.4.1/ota_updates/readme.html#updater-class
[HTTP_X_ESP_AP_MAC] => 1A:FE:AA:AA:AA:AA
[HTTP_X_ESP_FREE_SPACE] => 671744
[HTTP_X_ESP_SKETCH_SIZE] => 373940
[HTTP_X_ESP_CHIP_SIZE] => 4194304
[HTTP_X_ESP_SDK_VERSION] => 1.3.0
[HTTP_X_ESP_VERSION] => DOOR-7-g14f53a19
*/
header('Content-type: text/plain; charset=utf8', true);

// ################################
//   Functions up here
// ################################

function sha_of_file($path) {
  $sha256sum = hash_file("sha256",$path);
  return $sha256sum;
}

function sha_from_file($path) {
  // open file and seek to length-32bytes
  $start_of_hash = filesize($path) - 32;
  $fp = fopen($path, 'r');
  fseek($fp, $start_of_hash);
  $esp_hash = strtoupper(bin2hex(fread($fp,32)));
  fclose($fp);
  return $esp_hash;
}

function check_header($name, $value = false) {
    if(!isset($_SERVER[$name])) {
        return false;
    }
    if($value && $_SERVER[$name] != $value) {
        return false;
    }
    return true;
}

function sendFile($path) {
    header($_SERVER["SERVER_PROTOCOL"].' 200 OK', true, 200);
    header('Content-Type: application/octet-stream', true);
    header('Content-Disposition: attachment; filename='.basename($path));
    header('Content-Length: '.filesize($path), true);
    header('x-ESP-SHA256: '.sha_from_file($path), true);
	//echo "sending ",$path;
    readfile($path);
}

// ################################
//   Main code down here
// ################################

if(!check_header('HTTP_USER_AGENT', 'ESP-http-Update')) {
    header($_SERVER["SERVER_PROTOCOL"].' 403 Forbidden', true, 403);
    echo "only for ESP updater!\n";
    exit();
}

if( // If whatever called us didn't have the custom header, then ignore it
    !check_header('HTTP_X_ESP_STA_MAC')
	|| !check_header('HTTP_X_ESP_RUNNING_SHA256')
) {
    header($_SERVER["SERVER_PROTOCOL"].' 403 Forbidden', true, 403);
    echo "only for ESP updater! (header)\n";
    exit();
}

if(!isset($db[$_SERVER['HTTP_X_ESP_STA_MAC']])) {
    header($_SERVER["SERVER_PROTOCOL"].' 501 ESP MAC not configured for updates', true, 500);
	echo "ESP MAC not configured for updates\n";
	exit();
}

$localBinary = "./esp32/".$_SERVER['HTTP_X_ESP_STA_MAC']."/firmware.bin";
if(!file_exists($localBinary))
{
    header($_SERVER["SERVER_PROTOCOL"].' 404 File not found', true, 404);
	echo "Firmware for ".$_SERVER['HTTP_X_ESP_STA_MAC']." not found on server.\n";	
	exit();
}

if($_SERVER["HTTP_X_ESP_RUNNING_SHA256"] != sha_from_file($localBinary)) {
    sendFile($localBinary);
} else {
    header($_SERVER["SERVER_PROTOCOL"].' 304 Not Modified', true, 304);
}
