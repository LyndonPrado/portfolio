(function() {
  var ready, set_positions;

  ready = void 0;

  set_positions = function() {
    $('.card').each(function(i) {
      $(this).attr('data-pos', i + 1);
    });
  };

  ready = function() {
    $(document).on( 'turbolinks:load', function(){
      $('.sortable').sortable();

      
      $('.sortable').sortable().bind('sortupdate', function(e, ui) {
        var updated_order;
        updated_order = [];
        set_positons();
        $('.card').each(function(i) {
          updated_order.push;
          ({
            id: $(this).data('id'),
            position: i + 1
          });
        });
        $.ajax;
        ({
          type: 'PUT',
          url: '/portfolios/sort',
          data: {
            order: updated_order
          }
        });
      });
    });
  };

  $(document).ready(ready);

}).call(this);
