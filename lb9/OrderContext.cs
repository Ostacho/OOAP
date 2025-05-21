using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lb9
{
    public class OrderContext
    {
        public string CustomerName { get; }
        private IOrderState _state;

        public OrderContext(string customerName, IOrderState initialState = null)
        {
            CustomerName = customerName;
            _state = initialState ?? new OrderPlacedState();
        }

        public void SetState(IOrderState state)
        {
            _state = state;
        }

        public void Proceed()
        {
            _state.Proceed(this);
        }

        public void Cancel()
        {
            _state.Cancel(this);
        }

        public void PrintStatus()
        {
            Console.Write($"{CustomerName}'s ");
            _state.PrintStatus();
        }

        public void PrintShortStatus()
        {
            if (_state is OrderPlacedState)
                Console.Write("Order Placed");
            else if (_state is WaitingForPaymentState)
                Console.Write("Waiting for Payment");
            else if (_state is PaymentReceivedState)
                Console.Write("Payment Received");
            else if (_state is PackingOrderState)
                Console.Write("Packing Order");
            else if (_state is OrderShippedState)
                Console.Write("Order Shipped");
            else if (_state is OrderDeliveredState)
                Console.Write("Order Delivered");
            else if (_state is OrderReceivedState)
                Console.Write("Order Received");
            else if (_state is CancelledState)
                Console.Write("Cancelled");
            else
                Console.Write("Unknown State");
        }

        public bool CanProceed()
        {
            return _state is not OrderReceivedState && _state is not CancelledState;
        }

        public bool CanCancel()
        {
            return _state is OrderPlacedState
                || _state is WaitingForPaymentState;
        }



    }

}
