/*
 * A square grid of square cells
 */
function blinkengrid() {
    /*
     * Internal variables
     */
    var viz, svg
        , margin = { top: 5, right: 15, bottom: 5, left: 15 }
        , width = 500, height = 500 // square by default
        , id = "blinkengrid"
    ;
    var grid
        , count, across, down
        , coords = d3.scaleLinear()
                .range([0, width])
                .domain([0, count])
    ;
    var title
        , bitmap
        , font
    ;

    /*
     * Main function object
     */
    function widget(selection) {
        viz = selection;
        viz.selectAll(id).remove();

        svg = viz
          .append("svg")
            .attr("width", width + margin.left + margin.right)
            .attr("height", height + margin.top + margin.bottom)
            .attr("id", id)
          .append("g")
            .attr("transform", "translate(" + margin.left +","+ margin.top + ")")
        ;
        draw(d3.range(across * down).map(function(d, i) { return [i, 0]; })
              , true
          )
        ;
        blanken();
    } // widget()

    /*
     * Helper functions
     */
    function draw(data, clear) {
        var length = d3.min([width, height]), // length of a cell's side
            cells = svg.selectAll("rect").data(data, function(d) { return d[0]; })
        ;

        // Enter
        cells
          .enter().append("rect")
            .attr("id", function(d, i) { return "cell" + i; })
            .attr("x", function(d, i) { return coords(i % count); })
            .attr("y", function(d, i) { return coords((i / count) >> 0); })
            .attr("width",  function() { return length / count; })
            .attr("height", length / count)
        ;

        // Update
        cells
            .attr("class", "on")
        ;

        // Exit
        if(clear) { cells.exit().attr("class", "off"); }
    } // draw()


    function blanken() {
        svg.selectAll("rect")
            .attr("class", "off")
				;
    } // blanken()

    /*
     * Getter/Setter closure functions
     */
    widget.width = function(value) {
        if(!arguments.length) return width;

        width = value;
        coords.range([0, width]);
        return widget;
      } // widget.width()
    ;
    widget.height = function(value) {
        if(!arguments.length) return height;

        height = value;
        return widget;
      } // widget.height()
    ;
    widget.count = function(value) {
        if(!arguments.length) return count;

        count = value;
        coords.domain([0, count]);
        return widget;
      } // widget.count()
    ;
    widget.across = function(value) {
        if(!arguments.length) return across;

        across = value;
        return widget;
      } // widget.across()
    ;
    widget.down = function(value) {
        if(!arguments.length) return down;

        down = value;
        return widget;
      } // widget.down()
    ;
    widget.grid = function() {
        return svg;
      } // widget.grid()
    ;
    /*
     * Public API functions
     */
    widget.progress = function(value) {
        if(!value) return;

        var message = d3.range(Math.round(value * count))
                .map(function() { return [1,1,1]; })
            , offset = Math.ceil((count / 2)
                + ((message[0] == undefined ? 0 : message[0].length) + 2))
            , hm = d3.merge(message.map(function(columns, i) {
                    return columns.map(function (bit, j) {
                        return [(offset + j) * count + i, 0];
                    	});
            				}))
        ;

        var msg = svg.selectAll("rect")
                .data(hm, function(d) { return d[0]; })
                .attr("class", "progbar cooperator")
				;
        return widget;
    } // widget.progress()


    widget.blank = function(value) {
        blanken();

        return widget;
    } // widget.blank()

    widget.update = function(arg) {
        svg.selectAll("rect")
            .data(arg, function(d) { return d[0]; })
            .attr("class", function(d) { return dict[d[1]]; })
        ;
    } // widget.update()

    // Return the function object as the final thing
    return widget;
} // blinkengrid()
