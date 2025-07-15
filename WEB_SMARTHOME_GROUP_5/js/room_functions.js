// Hàm cập nhật cảnh báo nhiệt độ
function updateTemperatureWarning() {
  const tempGauge = document.querySelector('arc-gauge[unit="°C"]');
  const warningElement = document.getElementById('temperature-warning');
  if (!tempGauge || !warningElement) return;

  let value = parseFloat(tempGauge.getAttribute('value')) || 0;
  let warning = '';
  if (value <= 10) warning = 'Cold';
  else if (value <= 27) warning = 'Cool';
  else if (value <= 40) warning = 'Hot';
  else if (value <= 50) warning = 'Very Hot';
  else warning = 'May Catch Fire';

  warningElement.textContent = warning;
  warningElement.style.color = getTemperatureColor(value);
}

function getTemperatureColor(value) {
  if (value <= 10) return '#00bfff';
  if (value <= 27) return '#90ee90';
  if (value <= 40) return '#ffa500';
  if (value <= 50) return '#ff4500';
  return '#ff0000';
}

// Tương tự cho độ ẩm và chất lượng không khí
function updateHumidityWarning() {
  const humidGauge = document.querySelector('arc-gauge[unit="%"]');
  const warningElement = document.getElementById('humidity-warning');
  if (!humidGauge || !warningElement) return;

  let value = parseFloat(humidGauge.getAttribute('value')) || 0;
  let warning = '';
  if (value < 20) warning = 'Very Dry';
  else if (value <= 30) warning = 'Dry';
  else if (value <= 50) warning = 'Comfortable';
  else if (value <= 60) warning = 'Slightly Humid';
  else if (value <= 85) warning = 'Humid';
  else warning = 'Stuffy';

  warningElement.textContent = warning;
  warningElement.style.color = getHumidityColor(value);
}

function getHumidityColor(value) {
  if (value < 20) return '#ff4500';
  if (value <= 30) return '#ffa500';
  if (value <= 50) return '#90ee90';
  if (value <= 60) return '#00bfff';
  if (value <= 85) return '#ffa500';
  return '#ff0000';
}

function updateAirQualityWarning() {
  const airGauge = document.querySelector('arc-gauge[unit=""]');
  const warningElement = document.getElementById('air-quality-warning');
  if (!airGauge || !warningElement) return;

  let value = parseFloat(airGauge.getAttribute('value')) || 0;
  let warning = '';
  if (value <= 50) warning = 'Good';
  else if (value <= 100) warning = 'Moderate';
  else if (value <= 150) warning = 'Poor';
  else if (value <= 200) warning = 'Unhealthy';
  else if (value <= 300) warning = 'Very Unhealthy';
  else warning = 'Hazardous';

  warningElement.textContent = warning;
  warningElement.style.color = getAirQualityColor(value);
}

function getAirQualityColor(value) {
  if (value <= 50) return '#00ff00';
  if (value <= 100) return '#ffff00';
  if (value <= 150) return '#ffa500';
  if (value <= 200) return '#ff4500';
  if (value <= 300) return '#800080';
  return '#ff0000';
}

// Hàm cập nhật nhãn phần trăm
function updatePercentLabel(value, text) {
    let label = '';

    if (value == 0) {
        label = 'off';
    } else if (value < 35) {
        label = 'low';
    } else if (value <= 70) {
        label = 'medium';
    } else {
        label = 'high';
    }

    text.textContent = `${label} ${value}%`;
}

// Hàm cập nhật nhãn nhiệt độ
function updateTempLabel(value, text) {
    let label = '';

    if (value < 20) {
        label = 'low';
    } else if (value <= 28) {
        label = 'medium';
    } else {
        label = 'high';
    }

    text.textContent = `${label} ${value}°C`;
}

// Hàm cập nhật nền thanh trượt
function updateSliderBackground(slider) {
    const value = slider.value;
    const min = slider.min;
    const max = slider.max;
    const percent = ((value - min) / (max - min)) * 100;

    slider.style.background = `linear-gradient(to right, #b74b4b ${percent}%, #efe5e5 ${percent}%)`;
}

// Hàm cập nhật cảnh báo nhiệt độ
function updateTemperatureWarning() {
    const tempGauge = document.querySelector('arc-gauge[unit="°C"]');
    const warningElement = document.getElementById('temperature-warning');
    if (!tempGauge || !warningElement) return;

    let value = parseFloat(tempGauge.getAttribute('value')) || 0;
    let warning = '';
    if (value <= 10) warning = 'Cold';
    else if (value <= 27) warning = 'Cool';
    else if (value <= 40) warning = 'Hot';
    else if (value <= 50) warning = 'Very Hot';
    else warning = 'May Catch Fire';

    warningElement.textContent = warning;
    warningElement.style.color = getTemperatureColor(value);
}

function getTemperatureColor(value) {
    if (value <= 10) return '#00bfff';
    if (value <= 27) return '#90ee90';
    if (value <= 40) return '#ffa500';
    if (value <= 50) return '#ff4500';
    return '#ff0000';
}

// Tương tự cho độ ẩm và chất lượng không khí
function updateHumidityWarning() {
    const humidGauge = document.querySelector('arc-gauge[unit="%"]');
    const warningElement = document.getElementById('humidity-warning');
    if (!humidGauge || !warningElement) return;

    let value = parseFloat(humidGauge.getAttribute('value')) || 0;
    let warning = '';
    if (value < 20) warning = 'Very Dry';
    else if (value <= 30) warning = 'Dry';
    else if (value <= 50) warning = 'Comfortable';
    else if (value <= 60) warning = 'Slightly Humid';
    else if (value <= 85) warning = 'Humid';
    else warning = 'Stuffy';

    warningElement.textContent = warning;
    warningElement.style.color = getHumidityColor(value);
}

function getHumidityColor(value) {
    if (value < 20) return '#ff4500';
    if (value <= 30) return '#ffa500';
    if (value <= 50) return '#90ee90';
    if (value <= 60) return '#00bfff';
    if (value <= 85) return '#ffa500';
    return '#ff0000';
}

function updateAirQualityWarning() {
    const airGauge = document.querySelector('arc-gauge[unit=""]');
    const warningElement = document.getElementById('air-quality-warning');
    if (!airGauge || !warningElement) return;

    let value = parseFloat(airGauge.getAttribute('value')) || 0;
    let warning = '';
    if (value <= 50) warning = 'Good';
    else if (value <= 100) warning = 'Moderate';
    else if (value <= 150) warning = 'Poor';
    else if (value <= 200) warning = 'Unhealthy';
    else if (value <= 300) warning = 'Very Unhealthy';
    else warning = 'Hazardous';

    warningElement.textContent = warning;
    warningElement.style.color = getAirQualityColor(value);
}

function getAirQualityColor(value) {
    if (value <= 50) return '#00ff00';
    if (value <= 100) return '#ffff00';
    if (value <= 150) return '#ffa500';
    if (value <= 200) return '#ff4500';
    if (value <= 300) return '#800080';
    return '#ff0000';
}