class ArcGauge extends HTMLElement {
    constructor() {
        super();
        const shadow = this.attachShadow({ mode: 'open' });

        // Tạo cấu trúc HTML cho gauge
        const gauge = document.createElement('div');
        gauge.id = 'gauge';

        const minorTicks = document.createElement('div');
        minorTicks.id = 'minor-ticks';
        for (let i = 1; i <= 40; i++) {
            const span = document.createElement('span');
            span.style.setProperty('--i', i);
            minorTicks.appendChild(span);
        }

        const minorTicksBottomMask = document.createElement('div');
        minorTicksBottomMask.id = 'minor-ticks-bottom-mask';

        const bottomCircle = document.createElement('div');
        bottomCircle.id = 'bottom-circle';

        const svg = document.createElementNS('http://www.w3.org/2000/svg', 'svg');
        svg.setAttribute('version', '1.1');
        svg.setAttribute('baseProfile', 'full');
        svg.style.width = 'var(--gauge-width, 300px)';
        svg.style.height = 'var(--gauge-height, 300px)';
        svg.setAttribute('xmlns', 'http://www.w3.org/2000/svg');

        const gradient = document.createElementNS('http://www.w3.org/2000/svg', 'linearGradient');
        gradient.setAttribute('id', 'gradient');
        gradient.setAttribute('x1', '0');
        gradient.setAttribute('x2', '1');
        gradient.setAttribute('y1', '0');
        gradient.setAttribute('y2', '0');
        const stop1 = document.createElementNS('http://www.w3.org/2000/svg', 'stop');
        stop1.setAttribute('offset', '0%');
        stop1.setAttribute('stop-color', 'var(--gauge-start-color, #ff6f61)');
        const stop2 = document.createElementNS('http://www.w3.org/2000/svg', 'stop');
        stop2.setAttribute('offset', '100%');
        stop2.setAttribute('stop-color', 'var(--gauge-end-color, #6b5b95)');
        gradient.appendChild(stop1);
        gradient.appendChild(stop2);

        const circle = document.createElementNS('http://www.w3.org/2000/svg', 'circle');
        circle.setAttribute('cx', '50%'); // Tâm x ở giữa SVG
        circle.setAttribute('cy', '50%'); // Tâm y ở giữa SVG
        circle.setAttribute('r', '30%'); // Bán kính là 30% chiều rộng SVG
        circle.setAttribute('stroke', 'url(#gradient)');
        circle.setAttribute('fill', 'none');
        circle.setAttribute('stroke-width', 'var(--gauge-stroke-width, 12)');
        circle.setAttribute('stroke-linecap', 'round');
        // Bỏ transform="rotate" và sẽ xử lý điểm bắt đầu bằng stroke-dashoffset

        svg.appendChild(gradient);
        svg.appendChild(circle);

        const centerCircle = document.createElement('div');
        centerCircle.id = 'center-circle';
        const name = document.createElement('span');
        name.id = 'name';
        name.textContent = this.getAttribute('name') || '';
        const temperature = document.createElement('span');
        temperature.id = 'temperature';
        const unit = this.getAttribute('unit') || '°C';
        temperature.textContent = `${this.getAttribute('value') || 10}${unit}`;
        centerCircle.appendChild(name);
        centerCircle.appendChild(temperature);

        gauge.appendChild(minorTicks);
        gauge.appendChild(minorTicksBottomMask);
        gauge.appendChild(bottomCircle);
        gauge.appendChild(svg);
        gauge.appendChild(centerCircle);

        const style = document.createElement('style');
        style.textContent = `
            #gauge {
                position: relative;
                width: var(--gauge-width, 300px);
                height: var(--gauge-height, 300px);
                background: var(--gauge-bg, #ffffff);
                border-radius: var(--gauge-border-radius, 20px);
                display: flex;
                justify-content: center;
                align-items: center;
                box-shadow: var(--gauge-shadow, 0 15px 30px rgba(0, 0, 0, 0.2));
                overflow: hidden;
            }
            #minor-ticks {
                position: absolute;
                width: 80%;
                height: 80%;
                background: transparent;
                display: flex;
                justify-content: center;
                align-items: center;
            }
            #minor-ticks span {
                position: absolute;
                width: 100%;
                height: 1px;
                border-top: 1px solid var(--tick-color, #d1d5db);
                transform: rotate(calc((var(--i) - 1) * 9deg - 90deg));
                opacity: 0.5;
            }
            #minor-ticks::after {
                content: '';
                position: absolute;
                width: 93%;
                height: 93%;
                background: var(--ticks-bg, #fff);
                border-radius: 50%;
            }
            #minor-ticks-bottom-mask {
                display: none;
            }
            #bottom-circle {
                position: absolute;
                width: 70%;
                height: 70%;
                background: var(--bottom-bg, linear-gradient(135deg, #f3f4f6, #ffffff));
                border-radius: 50%;
                box-shadow: var(--bottom-shadow, inset 0 5px 10px rgba(0, 0, 0, 0.1), 0 5px 10px rgba(0, 0, 0, 0.05));
            }
            svg {
                position: absolute;
                filter: var(--svg-shadow, drop-shadow(0 5px 10px rgba(0, 0, 0, 0.15)));
                width: 100%;
                height: 100%;
            }
            svg circle {
                transition: stroke-dasharray 0.8s ease-in-out;
            }
            #center-circle {
                position: absolute;
                width: var(--center-width, 170px);
                height: var(--center-height, 170px);
                background: var(--center-bg, linear-gradient(180deg, #ffffff 0%, #e5e7eb 100%));
                border-radius: 50%;
                display: flex;
                justify-content: center;
                align-items: center;
                box-shadow: var(--center-shadow, 0 10px 20px rgba(0, 0, 0, 0.15), inset 0 2px 5px rgba(255, 255, 255, 0.5));
            }
            #center-circle::before {
                content: '';
                position: absolute;
                width: var(--inner-width, 145px);
                height: var(--inner-height, 145px);
                background: var(--inner-bg, linear-gradient(0deg, #ffffff 0%, #e5e7eb 100%));
                border-radius: 50%;
            }
            #name {
                position: absolute;
                font-size: var(--name-size, 1em);
                color: var(--name-color, #6b7280);
                font-weight: 700;
                top: var(--name-top, 30px);
                letter-spacing: 1px;
                text-transform: uppercase;
            }
            #temperature {
                position: absolute;
                font-size: var(--temp-size, 3.5em);
                color: var(--temp-color, #4b5563);
                font-weight: 700;
                text-shadow: var(--temp-shadow, 0 2px 4px rgba(0, 0, 0, 0.1));
            }
        `;
        shadow.appendChild(style);
        shadow.appendChild(gauge);

        // Khởi tạo gauge
        this.updateGauge();
    }

    static get observedAttributes() {
        return ['min', 'max', 'value', 'unit', 'name'];
    }

    attributeChangedCallback(name, oldValue, newValue) {
        if (name === 'value' || name === 'unit' || name === 'name') {
            this.updateGauge();
        }
    }

    updateGauge() {
        const min = parseInt(this.getAttribute('min') || 0);
        const max = parseInt(this.getAttribute('max') || 100);
        let value = parseInt(this.getAttribute('value') || 0);
        const unit = this.getAttribute('unit') || '';
        if (value < min) value = min;
        if (value > max) value = max;

        const temperature = this.shadowRoot.getElementById('temperature');
        temperature.textContent = `${value}${unit}`;

        const gauge = this.shadowRoot.getElementById('gauge');
        const arc = this.shadowRoot.querySelector('svg circle');

        // Lấy kích thước thực tế của gauge
        const gaugeWidth = parseFloat(getComputedStyle(gauge).width) || 300;
        const radius = gaugeWidth * 0.3; // Bán kính là 30% chiều rộng gauge
        const arc_length = 2 * Math.PI * radius; // Chu vi mới dựa trên bán kính
        const step = arc_length / (max - min);
        const dashValue = (value - min) * step;

        // Đặt stroke-dasharray
        arc.style.strokeDasharray = `${dashValue} ${arc_length - dashValue}`;

        // Dịch chuyển điểm bắt đầu về bên trái (180 độ)
        // Điểm 180 độ = nửa chu vi (arc_length / 2)
        const offset = arc_length / 2; // 180 độ
        arc.style.strokeDashoffset = offset;
    }

}

customElements.define('arc-gauge', ArcGauge);