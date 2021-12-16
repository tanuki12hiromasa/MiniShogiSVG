#include "SvgHtml.h"

void Html::SvgHtml(const Kyokumen& kyokumen) {
    std::ofstream fs("test.html");
    fs << (const char*)u8R"***(<!DOCTYPE html>
<html lang="ja">
<head>
  <meta charset="UTF-8">
  <title>Sample</title>
  <style>
    .image {
      margin: 0 auto;
      display: flex;
      align-items: center;
      width: 900px;
    }
    .image__svg {
      width: 400px;
    }
    .image__sep {
      flex-grow: 1;
      text-align: center;
    }
    .image__converted {
      width: 400px;
      height: 400px;
      border: 1px solid rgba(0, 0, 0, 0.5);
    }
  </style>
</head>
<body>
<div class="image">
  <div class="image__svg">)***";
    DrawSVG::drawKyokumenSVG(fs, kyokumen);
 fs << (const char*)u8R"***(</div>
  <div class="image__sep">
    <div>==&gt;&gt;</div>
    <div><button id="convert-button">変換する</button></div>
  </div>
  <div class="image__converted">
    <img src="" id="converted-image">
  </div>
</div>
<script>
  (function() {
    document.addEventListener('DOMContentLoaded', function() {
      document.getElementById('convert-button').addEventListener('click', function() {
        svg2imageData(document.getElementById('svg'), function(data) {
          console.log(data);
          document.getElementById('converted-image').src = data;
        }, function(error) {
          console.log(error);
          alert('failed to convert');
        });
      });
    });
    function svg2imageData(svgElement, successCallback, errorCallback) {
      var canvas = document.createElement('canvas');
      canvas.width = svgElement.width.baseVal.value;
      canvas.height = svgElement.height.baseVal.value;
      var ctx = canvas.getContext('2d');
      var image = new Image();
      image.onload = () => {
        ctx.drawImage(image, 0, 0, image.width, image.height);
        successCallback(canvas.toDataURL());
      };
      image.onerror = (e) => {
        errorCallback(e);
      };
      var svgData = new XMLSerializer().serializeToString(svgElement);
      image.src = 'data:image/svg+xml;charset=utf-8;base64,' + btoa(svgData);
    }
  }());
</script>
</body>
</html>)***";
}