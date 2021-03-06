export class SimpleGraph {
  private context: CanvasRenderingContext2D;
  private chartData: number[] = [];

  constructor(private canvas: HTMLCanvasElement) {
    this.context = this.canvas.getContext('2d');
    this.canvas.width  = this.canvas.clientWidth;
    this.canvas.height = this.canvas.clientHeight;
  }

  private static roundToPIPScale(number) {
    return Math.round(number * 1000000) / 1000000
  }

  private drawLine(sourceX, sourceY, destX, destY) {
    this.context.beginPath();
    this.context.moveTo(sourceX, sourceY);
    this.context.lineTo(destX, destY);
    this.context.strokeStyle = "white";
    this.context.stroke();
  }

  private static calcScale(data, boxSize) {
    const result: any = {};
    result.stepInPixel = boxSize / data.length;

    let min = Number.POSITIVE_INFINITY;
    let max = Number.NEGATIVE_INFINITY;
    for (let i = 0; i < data.length; i++) {
      if (data[i] < min) {
        min = data[i];
      }
      if (data[i] > max) {
        max = data[i];
      }

    }

    const delta = max - min;

    result.offsetY = min;
    result.multiplicatorY = ((boxSize / delta) / 100) * 90;

    return result;
  }

  private drawGraphAxis(boxSize) {
    let labelCount = 10;
    let stepSize = boxSize / labelCount;

    let min = Number.POSITIVE_INFINITY;
    let max = Number.NEGATIVE_INFINITY;
    for (let i = 0; i < this.chartData.length; i++) {
      if (this.chartData[i] < min) {
        min = this.chartData[i];
      }
      if (this.chartData[i] > max) {
        max = this.chartData[i];
      }
    }

    for (let i = 0; i <= labelCount; i++) {

      let delta = max - min;

      let currentScale = (1 / labelCount) * i;

      let label = SimpleGraph.roundToPIPScale(min + (delta * currentScale));
      this.context.fillText(label.toString(), boxSize + 5, ((stepSize * i) * -1) + boxSize);
    }
  }

  private drawGraph() {

    this.context.clearRect(0, 0, this.canvas.width, this.canvas.height);
    let boxSize = this.canvas.width - 50;

    this.drawLine(0, 0, 0, boxSize);
    this.drawLine(0, 0, boxSize, 0);
    this.drawLine(boxSize, 0, boxSize, boxSize);
    this.drawLine(0, boxSize, boxSize, boxSize);

    const scale = SimpleGraph.calcScale(this.chartData, boxSize);

    let stepInPixel = scale.stepInPixel;
    let multiplicatorY = scale.multiplicatorY;
    let offsetY = scale.offsetY;

    let offset = 0;
    let lastY = 0;
    for (let i = 0; i < this.chartData.length; i++) {
      let currentY = ((this.chartData[i] * multiplicatorY) * -1) + (offsetY * multiplicatorY) + boxSize;
      if (i == 0) {
        lastY = currentY;
      }

      this.drawLine(offset, lastY, offset + stepInPixel, currentY);
      offset += stepInPixel;
      lastY = currentY;

    }
    this.drawGraphAxis(boxSize);
  }

  public add(value: number) {
    this.chartData.push(value);
    if (this.chartData.length > 50) {
      this.chartData.splice(0, 1);
    }

    this.drawGraph();
  }
}



